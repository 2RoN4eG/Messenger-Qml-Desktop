#include "t_json_peer_preview_parser.h"
#include "t_json_defines.h"

#include "../interfaces/i_peer_context_setter.h"


namespace
{
    constexpr const char* self_field                    = "self";
    constexpr const char* peers_field                   = "peers";
    constexpr const char* peers_id_field                = "peer_id";
    constexpr const char* peers_nickname_field          = "nickname";
    constexpr const char* peers_avatars_field           = "avatars";
    constexpr const char* peers_avatar_url_field        = "url";
    constexpr const char* peers_avatar_thumb_hash_field = "thumb_hash";

    void process_peer_avatar(const t_qt_json_object& json_object, const t_peer_id peer_id, i_peer_context_setter& context_setter, t_image_id_generator& avatar_id_generator)
    {
        context_setter.set_peer_avatar_component(peer_id,
                                                 avatar_id_generator.get_value_and_generate_next(),
                                                 json_object[peers_avatar_url_field].toString(),
                                                 json_object[peers_avatar_thumb_hash_field].toString().toStdString()
                                                  );
    }

    void process_peer_avatars(const t_qt_json_array& json_array, const t_peer_id peer_id, i_peer_context_setter& context_setter, t_image_id_generator& avatar_id_generator) {

        for (const t_qt_json_value& json_value : json_array)
        {
            process_peer_avatar(json_value.toObject(), peer_id, context_setter, avatar_id_generator);
        }
    }

    void process_peer(const t_qt_json_object& json_object, i_peer_context_setter& context_setter, t_image_id_generator& avatar_id_generator) {
        const t_peer_id peer_id = json_object[peers_id_field].toInt();
        t_nickname&& nickname   = json_object[peers_nickname_field].toString().toStdString();

        context_setter.set_peer_component(peer_id, std::move(nickname));
        context_setter.set_peer_default_avatar_component(peer_id, avatar_id_generator.get_value_and_generate_next());

        process_peer_avatars(json_object[peers_avatars_field].toArray(), peer_id, context_setter, avatar_id_generator);
        // parse_peer_latest_message(messenger_context_getter, peer_id, json_object["latest_message"].toObject());
    }

    void process_peers(const t_qt_json_array& json_array, i_peer_context_setter& context_setter, t_image_id_generator& avatar_id_generator) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer(json_value.toObject(), context_setter, avatar_id_generator);
        }
    }
}

t_json_peer_preview_processor::t_json_peer_preview_processor(i_peer_context_setter& messenger_context_getter, t_image_id_generator& avatar_id_generator)
    : _peer_context_setter { messenger_context_getter }
    , _avatar_id_generator { avatar_id_generator }
{
}

void t_json_peer_preview_processor::operator()(const std::string_view json) const {
    t_qt_json_parce_error error;
    t_qt_json_document document = t_qt_json_document::fromJson(QByteArray::fromRawData(json.data(), json.size()), &error);

    if (error.error != t_qt_json_parce_error::NoError)
    {
        qWarning() << "Error parsing JSON:" << error.errorString();
        qWarning() << "JSON:" << t_qt_json { json.data() };
        return;
    }

    const t_qt_json_object& json_object = document.object();

    process_peer (json_object[self_field].toObject(), _peer_context_setter, _avatar_id_generator);
    process_peers(json_object[peers_field].toArray(), _peer_context_setter, _avatar_id_generator);

    return;
}
