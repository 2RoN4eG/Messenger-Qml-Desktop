#include "t_peer_context_getter.h"

#include "../interfaces/i_storage_message_info.h"
#include "../interfaces/i_storage_image_info.h"
#include "../interfaces/i_storage_peer_info.h"

namespace memory
{

    t_peer_context_getter::t_peer_context_getter(const i_peer_info_storage& peer_info_storage,
                                                 const i_image_info_storage& image_info_storage,
                                                 const i_message_info_storage& message_info_storage)
        : _peer_info_storage { peer_info_storage }
        , _image_info_storage { image_info_storage }
        , _message_info_storage { message_info_storage }
    {
    }


    const i_peer_info_storage& t_peer_context_getter::peer_info_storage() const {
        return _peer_info_storage;
    }

    const i_image_info_storage& t_peer_context_getter::image_info_storage() const {
        return _image_info_storage;
    }

    const i_message_info_storage& t_peer_context_getter::message_info_storage() const {
        return _message_info_storage;
    }


    const t_nickname t_peer_context_getter::get_peer_nickname(const t_peer_id peer_id) const {
        const t_nickname& nickname = _peer_info_storage.get_nickname(peer_id);

        return nickname;
    }


    const t_image_id t_peer_context_getter::get_peer_latest_avatar_id(const t_peer_id peer_id) const {
        const t_avatar_id avatar_id = _image_info_storage.get_latest_avatar_id(peer_id);

        return avatar_id;
    }

    const t_image_id t_peer_context_getter::get_peer_default_avatar_id(const t_peer_id peer_id) const {
        const t_default_avatar_id default_avatar_id = _image_info_storage.get_default_avatar_id(peer_id);

        return default_avatar_id;
    }

    const bool t_peer_context_getter::does_peer_message_photo_exist(const t_message_id message_id) const {
        return {};
    }

    const t_photo_id t_peer_context_getter::get_peer_message_photo(const t_message_id message_id) const {
        return {};
    }

    const t_message_text t_peer_context_getter::get_peer_message_text(const t_message_id message_id) const {
        return {};
    }

    const t_message_timestamp t_peer_context_getter::get_peer_message_timestamp(const t_message_id message_id) const {
        return {};
    }

} // namespace memory
