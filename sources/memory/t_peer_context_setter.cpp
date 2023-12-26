#include "t_peer_context_setter.h"

#include "../interfaces/i_storage_image_info.h"
#include "../interfaces/i_storage_peer_info.h"
#include "../interfaces/i_storage_message_info.h"

namespace memory
{

t_peer_context_setter::t_peer_context_setter(i_peer_info_storage& peer_info_storage,
                                             i_image_info_storage& image_info_storage,
                                             i_message_info_storage& message_info_storage)
    : _peer_info_storage { peer_info_storage }
    , _image_info_storage { image_info_storage }
    , _message_info_storage { message_info_storage }
{
}

void t_peer_context_setter::set_peer_info(const t_peer_id peer_id, t_nickname&& nickname)
{
    _peer_info_storage.set_peer_info(peer_id, std::move(nickname));
}

void t_peer_context_setter::set_peer_default_avatar_image_info(const t_peer_id peer_id,
                                                               const t_avatar_id avatar_id)
{
    _image_info_storage.set_default_avatar_image_info(peer_id, avatar_id);
}

void t_peer_context_setter::set_peer_avatar_image_info(const t_peer_id peer_id,
                                                       const t_avatar_id avatar_id,
                                                       const t_url& url,
                                                       const t_thumb_hash& thumb_hash)
{
    _image_info_storage.set_avatar_image_info(peer_id, avatar_id, url, thumb_hash);
}

void t_peer_context_setter::set_peer_message_info(const t_peer_id peer_id,
                                                  const t_message_id message_id,
                                                  const t_message_text& text,
                                                  const t_message_timestamp timestamp)
{
    _message_info_storage.set_message_info(message_id, peer_id, text, timestamp);
}

void t_peer_context_setter::set_peer_message_info(const t_peer_id peer_id,
                                                  const t_message_id message_id,
                                                  const t_photo_id photo_id,
                                                  const t_message_text& text,
                                                  const t_message_timestamp timestamp)
{
    _message_info_storage.set_message_info(message_id, peer_id, photo_id, text, timestamp);
}

void t_peer_context_setter::set_peer_message_photo_image_info(const t_peer_id peer_id,
                                                              const t_photo_id photo_id,
                                                              const t_url& url,
                                                              const t_thumb_hash& thumb_hash)
{
    _image_info_storage.set_photo_image_info(peer_id, photo_id, url, thumb_hash);
}

} // namespace memory
