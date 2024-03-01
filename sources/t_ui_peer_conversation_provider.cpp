#include "t_ui_peer_conversation_provider.h"
#include <iostream>

t_ui_peer_conversation_provider::t_ui_peer_conversation_provider(const t_message_info_storage* messages)
    : _messages { *messages }
{
}

int t_ui_peer_conversation_provider::count() const {
    return (int)_messages.size();
}

QString t_ui_peer_conversation_provider::latest_avatar_id(int index) const {
    return "";
}

QString t_ui_peer_conversation_provider::peer_message_nickname(int index) const {
    return "";
}

QString t_ui_peer_conversation_provider::peer_message_photo(int index) const {
    const t_photo_id photo_id = _messages[index]._photo_id;

    // std::cout << "photo_id is " << (photo_id == t_photo_id::none() ? "" : "none ") << photo_id << std::endl;
    // if (photo_id == t_photo_id::none()) {
    //     return "";
    // }

    return "image://photos/" + QString::number(photo_id.value());
}

QString t_ui_peer_conversation_provider::peer_message_text(int index) const {
    const t_message_text& text = _messages[index]._text;

    return QString::fromStdString(text);
}

QString t_ui_peer_conversation_provider::peer_message_timestamp(int index) const {
    const t_message_timestamp timestamp = _messages[index]._timestamp;

    return QString::number(timestamp);
}

