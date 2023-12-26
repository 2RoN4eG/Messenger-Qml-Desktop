#include "t_qt_peer_conversation_provider.h"

#include "../interfaces/i_peer_context_getter.h"
#include "../memory/t_storage_message_info.h"

#include <iostream>


t_peer_conversation_provider::t_peer_conversation_provider(const i_peer_context_getter* context_getter)
    : _context_getter { *context_getter }
    , _message_info_storage { _context_getter.message_info_storage() }
    , _message_infos { _message_info_storage.message_infos() }
{
}

int t_peer_conversation_provider::size() const {
    return (int)_message_infos.size();
}

QString t_peer_conversation_provider::latest_avatar_id(int index) const {
    const t_message_id message_id = _message_info_storage[index];

    const t_peer_id peer_id = _message_info_storage.get_message_peer_id(message_id);

    try
    {
        const t_avatar_id avatar_id = _context_getter.get_peer_latest_avatar_id(peer_id);

        return "image://avatars/" + QString::number(avatar_id.value());
    }
    catch (const std::exception& exception)
    {
        std::cerr << "exception: " << exception.what() << std::endl;

        const t_avatar_id avatar_id = _context_getter.get_peer_default_avatar_id(peer_id);

        return "";
        return "image://default/" + QString::number(avatar_id.value());
    }
}

QString t_peer_conversation_provider::message_peer_nickname(int index) const {
    const t_message_id message_id = _message_info_storage[index];

    const t_peer_id peer_id = _message_info_storage.get_message_peer_id(message_id);

    const t_nickname nickname = _context_getter.get_peer_nickname(peer_id);

    std::cout << "message: " << message_id << ", peer: " << peer_id << ", nickname: " << nickname << std::endl;

    return QString::fromStdString(nickname);
}

QString t_peer_conversation_provider::message_photo(int index) const {
    const t_message_id message_id = _message_info_storage[index];
    
    const t_photo_id photo_id = _message_info_storage.get_message_photo_id(message_id);

    if (photo_id == t_avatar_id::none()) {
        return "";
    }

    return "image://photos/" + QString::number(photo_id.value());
}

QString t_peer_conversation_provider::message_text(int index) const {
    const t_message_id message_id = _message_info_storage[index];

    const t_message_text& text = _message_info_storage.get_message_text(message_id);

    return QString::fromStdString(text);
}

QString t_peer_conversation_provider::message_timestamp(int index) const {
    const t_message_id message_id = _message_info_storage[index];
    
    const t_message_timestamp timestamp = _message_info_storage.get_message_timestamp(message_id);

    return QString::number(timestamp);
}
