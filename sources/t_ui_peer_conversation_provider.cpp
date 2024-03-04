#include "t_ui_peer_conversation_provider.h"

#include "interface/i_messenger_context_getter.h"

t_ui_peer_conversation_provider::t_ui_peer_conversation_provider(const i_messenger_context_getter* context_getter)
    : _context_getter { *context_getter }
    , _message_info_storage { _context_getter.message_info_storage() }

{
}

int t_ui_peer_conversation_provider::count() const {
    return (int)_message_info_storage.size();
}

QString t_ui_peer_conversation_provider::peer_latest_avatar_id(int index) const {
    return "";
}

QString t_ui_peer_conversation_provider::peer_message_nickname(int index) const {
    const t_peer_id peer_id = _message_info_storage[index]._peer_id;

    const t_nickname nickname = _context_getter.get_peer_nickname(peer_id);

    return QString::fromStdString(nickname);
}

QString t_ui_peer_conversation_provider::peer_message_photo(int index) const {
    const t_photo_id photo_id = _message_info_storage[index]._photo_id;

    if (photo_id == t_photo_id::none()) {
        return "";
    }

    return "image://photos/" + QString::number(photo_id.value());
}

QString t_ui_peer_conversation_provider::peer_message_text(int index) const {
    const t_message_text& text = _message_info_storage[index]._text;

    return QString::fromStdString(text);
}

QString t_ui_peer_conversation_provider::peer_message_timestamp(int index) const {
    const t_message_timestamp timestamp = _message_info_storage[index]._timestamp;

    return QString::number(timestamp);
}

