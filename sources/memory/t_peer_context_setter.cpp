#include "t_peer_context_setter.h"

#include "../interfaces/i_image_component_storage.hpp"
#include "../interfaces/i_peer_component_storage.hpp"
#include "../interfaces/i_message_component_storage.hpp"


namespace memory
{
    t_peer_context_setter::t_peer_context_setter(i_peer_component_storage& peer_component_storage,
                                                 i_image_component_storage& image_component_storage,
                                                 i_message_component_storage& message_component_storage)
        : _peer_component_storage { peer_component_storage }
        , _image_component_storage { image_component_storage }
        , _message_component_storage { message_component_storage }
    {
    }

    void t_peer_context_setter::set_peer_component(const t_peer_id peer_id, t_nickname&& nickname)
    {
        _peer_component_storage.set_peer_component(peer_id, std::move(nickname));
    }

    void t_peer_context_setter::set_peer_default_avatar_component(const t_peer_id peer_id, const t_avatar_id avatar_id)
    {
        _image_component_storage.set_default_avatar_component(peer_id, avatar_id);
    }

    void t_peer_context_setter::set_peer_avatar_component(const t_peer_id peer_id, const t_avatar_id avatar_id, const t_url& url, const t_thumb_hash& thumb_hash)
    {
        _image_component_storage.set_avatar_component(peer_id, avatar_id, url, thumb_hash);
    }

    void t_peer_context_setter::set_peer_message_component(const t_peer_id peer_id, const t_message_id message_id, const t_message_text& text, const t_message_timestamp timestamp)
    {
        _message_component_storage.set_message_component(message_id, peer_id, text, timestamp);
    }

    void t_peer_context_setter::set_peer_message_component(const t_peer_id peer_id, const t_message_id message_id, const t_photo_id photo_id, const t_message_text& text, const t_message_timestamp timestamp)
    {
        _message_component_storage.set_message_component(message_id, peer_id, photo_id, text, timestamp);
    }

    void t_peer_context_setter::set_peer_message_photo_component(const t_peer_id peer_id, const t_photo_id photo_id, const t_url& url, const t_thumb_hash& thumb_hash)
    {
        _image_component_storage.set_photo_component(peer_id, photo_id, url, thumb_hash);
    }
} // namespace memory
