#include "t_json_peer_info_parser.h"

#include "t_fs.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include <iostream>

#include "interface/i_peer_context_setter.h"


namespace {
    using t_qt_json_object = QJsonObject;
    using t_qt_json_array = QJsonArray;
    using t_qt_json_value = QJsonValue;
    
    void process_peer_avatar(const t_qt_json_object& json_object, const t_peer_id peer_id, i_peer_context_setter& peer_info_storage, t_image_id_generator& avatar_id_generator) {
        peer_info_storage.set_peer_avatar_image_info(
                peer_id,
                avatar_id_generator.get_value_and_generate_next(),
                json_object["url"].toString(),
                json_object["thumb_hash"].toString().toStdString()
            );
    }

    void process_peer_avatars(const t_qt_json_array& json_array, const t_peer_id peer_id, i_peer_context_setter& peer_info_storage, t_image_id_generator& avatar_id_generator) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer_avatar(json_value.toObject(), peer_id, peer_info_storage, avatar_id_generator);
        }
    }
    
    void process_peer(const t_qt_json_object& json_object, i_peer_context_setter& peer_info_storage, t_image_id_generator& avatar_id_generator) {
        t_peer_id peer_id   = json_object["peer_id"].toInt();
        t_nickname&& nickname = json_object["nickname"].toString().toStdString();

        peer_info_storage.set_peer_info(peer_id, std::move(nickname));

        process_peer_avatars(json_object["avatars"].toArray(), peer_id, peer_info_storage, avatar_id_generator);
        // parse_peer_last_message(peer_info_storage, peer_id, json_object["last_message"].toObject());
    }

    void process_peers(const t_qt_json_array& json_array, i_peer_context_setter& peer_info_storage, t_image_id_generator& avatar_id_generator) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer(json_value.toObject(), peer_info_storage, avatar_id_generator);
        }
    }
}


t_json_peer_info_processor::t_json_peer_info_processor(i_peer_context_setter& peer_info_storage, t_image_id_generator& avatar_id_generator)
    : _peer_context_setter { peer_info_storage }
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

    process_peers(json_object["peers"].toArray(), _peer_context_setter, _avatar_id_generator);

    return;
}

