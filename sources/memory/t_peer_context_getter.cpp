#include "t_peer_context_getter.h"

#include "../interfaces/i_message_component_storage.hpp"
#include "../interfaces/i_image_component_storage.hpp"
#include "../interfaces/i_peer_component_storage.hpp"

#include <iostream>


namespace memory
{
    t_peer_context_getter::t_peer_context_getter(const i_peer_component_storage& peer_component_storage,
                                                 const i_image_component_storage& image_component_storage,
                                                 const i_message_component_storage& message_component_storage)
        : _peer_component_storage { peer_component_storage }
        , _image_component_storage { image_component_storage }
        , _message_component_storage { message_component_storage }
    {
    }


    const i_peer_component_storage& t_peer_context_getter::peer_component_storage() const
    {
        return _peer_component_storage;
    }

    const i_image_component_storage& t_peer_context_getter::image_component_storage() const
    {
        return _image_component_storage;
    }

    const i_message_component_storage& t_peer_context_getter::message_component_storage() const
    {
        return _message_component_storage;
    }


    const t_nickname t_peer_context_getter::get_peer_nickname(const t_peer_id peer_id) const
    {
        std::cout << "get_peer_nickname(const t_peer_id peer_id { " << peer_id << " }) const" << std::endl;

        return _peer_component_storage.get_nickname(peer_id);
    }

    const bool t_peer_context_getter::does_peer_avatar_exist(const t_peer_id peer_id) const
    {
        return {};
    }

    const t_image_id t_peer_context_getter::get_peer_latest_avatar_id(const t_peer_id peer_id) const
    {
        return _image_component_storage.get_latest_avatar_id(peer_id);
    }

    const t_image_id t_peer_context_getter::get_peer_default_avatar_id(const t_peer_id peer_id) const
    {
        return _image_component_storage.get_default_avatar_id(peer_id);
    }


    const bool t_peer_context_getter::does_peer_message_photo_exist(const t_message_id message_id) const
    {
        return {};
    }

    const t_photo_id t_peer_context_getter::get_peer_message_photo(const t_message_id message_id) const
    {
        return {};
    }

    const t_message_text t_peer_context_getter::get_peer_message_text(const t_message_id message_id) const
    {
        return {};
    }

    const t_message_timestamp t_peer_context_getter::get_peer_message_timestamp(const t_message_id message_id) const
    {
        return {};
    }


    const t_message_text t_peer_context_getter::get_room_latest_message_preview(const t_room_id room_id) const
    {
        return {};
    }

    const t_message_timestamp t_peer_context_getter::get_room_latest_message_timestamp(const t_room_id room_id) const
    {
        return {};
    }

} // namespace memory
