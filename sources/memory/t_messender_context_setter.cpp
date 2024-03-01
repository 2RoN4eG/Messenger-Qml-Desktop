#include "t_messender_context_setter.h"

#include <iostream>


namespace memory
{

t_messenger_context_setter::t_messenger_context_setter(t_peer_info_storage& peer_infos,
                                             i_image_info_storage& image_info_storage,
                                                       t_message_info_storage& messages)
    : _peer_infos { peer_infos }
    , _image_info_storage { image_info_storage }
    , _messages { messages }
{
}


void t_messenger_context_setter::set_peer_info(const t_peer_id peer_id, t_nickname&& nickname) {
    _peer_infos.emplace(t_peer_info { peer_id, std::move(nickname) });
}

void t_messenger_context_setter::set_peer_avatar_image_info(const t_peer_id peer_id, t_avatar_id avatar_id, const t_url& url, const t_thumb_hash& thumb_hash) {
    _image_info_storage.set_avatar_image_info(peer_id, avatar_id, url, thumb_hash);
}


void t_messenger_context_setter::set_peer_message_info(const t_peer_id peer_id, const t_message_text& text, const t_message_timestamp timestamp) {
    set_peer_message_info(peer_id, t_photo_id::none(), text, timestamp);
}

void t_messenger_context_setter::set_peer_message_info(const t_peer_id peer_id, const t_photo_id photo_id, const t_message_text& text, const t_message_timestamp timestamp) {
    _messages.emplace_back(peer_id, photo_id, text, timestamp);
}

void t_messenger_context_setter::set_peer_message_photo_image_info(const t_peer_id peer_id, const t_photo_id photo_id, const t_url& url, const t_thumb_hash& thumb_hash) {
    _image_info_storage.set_photo_image_info(peer_id, photo_id, url, thumb_hash);
}


// const t_avatar_id t_messenger_context_setter::latest_avatar_id(const t_peer_id peer_id) const {
//     return _image_info_storage.get_latest_avatar_id(peer_id);
// }

} // namespace memory
