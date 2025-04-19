#include "t_json_peer_message_processor.h"
#include "t_json_defines.h"

#include "../interfaces/i_peer_context_setter.h"

#include <QDebug>


namespace {
    constexpr const char* room_field                      = "room_id";
    constexpr const char* messages_field                  = "messages";
    constexpr const char* messages_text_field             = "text";
    constexpr const char* messages_timestamp_field        = "timestamp";
    constexpr const char* messages_peer_field             = "peer_id";
    constexpr const char* messages_photo_field            = "photo";
    constexpr const char* messages_photo_url_field        = "url";
    constexpr const char* messages_photo_thumb_hash_field = "thumb_hash";

    void process_peer_message_photo(const t_qt_json_object& json_object,
                                    const t_peer_id peer_id,
                                    const t_image_id photo_id,
                                    i_peer_context_setter& peer_context_setter) {

        const t_url url = json_object[messages_photo_url_field].toString();
        const t_thumb_hash thumb_hash = json_object[messages_photo_thumb_hash_field].toString().toStdString();

        peer_context_setter.set_peer_message_photo_component(peer_id, photo_id, url, thumb_hash);
    }

    void process_peer_message(const t_qt_json_object& json_object,
                              i_peer_context_setter& peer_context_setter,
                              t_message_id_generator& message_id_generator,
                              t_image_id_generator& photo_id_generator) {
        const t_peer_id peer_id = json_object[messages_peer_field].toInt();

        const t_message_text& text = json_object[messages_text_field].toString().toStdString();
        const t_message_timestamp timestamp = json_object[messages_timestamp_field].toInt();

        const t_message_id message_id = message_id_generator.get_value_and_generate_next();

        if (json_object.contains(messages_photo_field)) {
            const t_photo_id photo_id = photo_id_generator.get_value_and_generate_next();

            const t_qt_json_object& photo_object = json_object[messages_photo_field].toObject();
            process_peer_message_photo(photo_object, peer_id, photo_id, peer_context_setter);

            peer_context_setter.set_peer_message_component(peer_id, message_id, photo_id, text, timestamp);

            return;
        }

        peer_context_setter.set_peer_message_component(peer_id, message_id, text, timestamp);
    }

    void process_peer_messages(const t_qt_json_array& json_array, i_peer_context_setter& peer_context_setter, t_message_id_generator& message_id_generator, t_image_id_generator& photo_id_generator) {
        for (const t_qt_json_value& json_value : json_array) {
            process_peer_message(json_value.toObject(), peer_context_setter, message_id_generator, photo_id_generator);
        }
    }
}

t_json_peer_message_processor::t_json_peer_message_processor(i_peer_context_setter& peer_context_setter,
                                                             t_message_id_generator& message_id_generator,
                                                             t_image_id_generator& photo_id_generator)
    : _peer_context_setter { peer_context_setter }
    , _message_id_generator { message_id_generator }
    , _photo_id_generator { photo_id_generator }
{
}

void t_json_peer_message_processor::operator()(const t_json_string_view json) const {
    t_qt_json_parce_error error;
    t_qt_json_document document = QJsonDocument::fromJson(QByteArray::fromRawData(json.data(), json.size()), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "t_json_peer_message_processor: Error parsing JSON:" << error.errorString();
        qWarning() << "t_json_peer_message_processor: JSON:" << t_qt_json { json.data() };
        return;
    }

    const t_qt_json_object& json_object = document.object();

    process_peer_messages(json_object[messages_field].toArray(), _peer_context_setter, _message_id_generator, _photo_id_generator);

    return;
}
