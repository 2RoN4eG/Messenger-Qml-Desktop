#include "t_json_peer_info_parser.h"

#include "t_json_defines.h"
#include "interface/i_messenger_context_setter.h"

#include <iostream>


namespace {
    constexpr const char* t_self_field                      = "self";
    constexpr const char* t_peers_field                     = "peers";
    constexpr const char* t_peer_id_field                   = "peer_id";
    constexpr const char* t_peer_nickname_field             = "nickname";
    constexpr const char* t_peer_avatars_field              = "avatars";
    constexpr const char* t_peer_avatar_url_field           = "url";
    constexpr const char* t_peer_avatar_thumb_hash_field    = "thumb_hash";


    void process_peer_avatar(const t_qt_json_object& json_object,
                             const t_peer_id peer_id,
                             i_messenger_context_setter& messenger_context_getter,
                             t_image_id_generator& avatar_id_generator) {
        messenger_context_getter.set_peer_avatar_image_info(
                peer_id,
                avatar_id_generator.get_value_and_generate_next(),
                json_object[t_peer_avatar_url_field].toString(),
                json_object[t_peer_avatar_thumb_hash_field].toString().toStdString()
            );
    }

    void process_peer_avatars(const t_qt_json_array& json_array,
                              const t_peer_id peer_id,
                              i_messenger_context_setter& messenger_context_getter,
                              t_image_id_generator& avatar_id_generator) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer_avatar(json_value.toObject(), peer_id, messenger_context_getter, avatar_id_generator);
        }
    }

    void process_peer(const t_qt_json_object& json_object, i_messenger_context_setter& messenger_context_getter, t_image_id_generator& avatar_id_generator) {
        t_peer_id peer_id     = json_object[t_peer_id_field].toInt();
        t_nickname&& nickname = json_object[t_peer_nickname_field].toString().toStdString();

        messenger_context_getter.set_peer_info(peer_id, std::move(nickname));

        process_peer_avatars(json_object[t_peer_avatars_field].toArray(), peer_id, messenger_context_getter, avatar_id_generator);
        // parse_peer_last_message(messenger_context_getter, peer_id, json_object["last_message"].toObject());
    }

    void process_peers(const t_qt_json_array& json_array, i_messenger_context_setter& messenger_context_getter, t_image_id_generator& avatar_id_generator) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer(json_value.toObject(), messenger_context_getter, avatar_id_generator);
        }
    }
}


t_json_peer_info_processor::t_json_peer_info_processor(i_messenger_context_setter& messenger_context_getter, t_image_id_generator& avatar_id_generator)
    : _peer_context_setter { messenger_context_getter }
    , _avatar_id_generator { avatar_id_generator }
{
}

void t_json_peer_info_processor::operator()(const std::string_view json) const {
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(QByteArray::fromRawData(json.data(), json.size()), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        qWarning() << "JSON:" << QString { json.data() };
        return;
    }

    const t_qt_json_object& json_object = document.object();

    process_peer(json_object[t_self_field].toObject(), _peer_context_setter, _avatar_id_generator);
    process_peers(json_object[t_peers_field].toArray(), _peer_context_setter, _avatar_id_generator);

    return;
}
