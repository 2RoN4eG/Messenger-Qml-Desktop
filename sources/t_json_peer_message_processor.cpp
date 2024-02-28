#include "t_json_peer_message_processor.h"

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

    constexpr char* t_message_text_field             = "text";
    constexpr char* t_message_timestamp_field        = "timestamp";
    constexpr char* t_message_peer_field             = "peer_id";
    constexpr char* t_message_photo_field            = "photo";
    constexpr char* t_message_photo_url_field        = "url";
    constexpr char* t_message_photo_thumb_hash_field = "thumb_hash";

    void process_peer_message_photo(const t_qt_json_object& json_object, const t_peer_id peer_id, t_image_id& photo_id, i_peer_context_setter& peer_context_setter) {
        t_url url = json_object[t_message_photo_url_field].toString();
        t_thumb_hash thumb_hash = json_object[t_message_photo_thumb_hash_field].toString().toStdString();

        peer_context_setter.set_peer_message_photo_image_info(peer_id, photo_id, url, thumb_hash);
    }

    void process_peer_message(const t_qt_json_object& json_object, i_peer_context_setter& peer_context_setter, t_image_id_generator& photo_id_generator) {
        const t_peer_id peer_id = json_object[t_message_peer_field].toInt();

        const t_message_text& text = json_object[t_message_text_field].toString().toStdString();
        const t_message_timestamp timestamp = json_object[t_message_timestamp_field].toInt();

        if (json_object.contains(t_message_photo_field)) {
            t_photo_id photo_id = photo_id_generator.get_value_and_generate_next();

            const t_qt_json_object& photo_object = json_object[t_message_photo_field].toObject();
            process_peer_message_photo(photo_object, peer_id, photo_id, peer_context_setter);

            peer_context_setter.set_peer_message_info(peer_id, photo_id, text, timestamp);

            return;
        }

        peer_context_setter.set_peer_message_info(peer_id, text, timestamp);
    }

    void process_peer_messages(const t_qt_json_array& json_array, i_peer_context_setter& peer_context_setter, t_image_id_generator& photo_id_generator) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer_message(json_value.toObject(), peer_context_setter, photo_id_generator);
        }
    }
}


t_json_peer_message_processor::t_json_peer_message_processor(i_peer_context_setter& peer_context_setter, t_image_id_generator& photo_id_generator)
    : _peer_context_setter { peer_context_setter }
    , _photo_id_generator { photo_id_generator }
{
}

void t_json_peer_message_processor::operator()(const std::string_view json) const {
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(QByteArray::fromRawData(json.data(), json.size()), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing JSON:" << error.errorString();
        qWarning() << "JSON:" << QString { json.data() };
        return;
    }

    const t_qt_json_object& json_object = document.object();

    process_peer_messages(json_object["messages"].toArray(), _peer_context_setter, _photo_id_generator);

    return;
}
