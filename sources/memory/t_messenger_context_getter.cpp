#include "t_messenger_context_getter.h"

namespace memory
{

t_messenger_context_getter::t_messenger_context_getter(const t_peer_infos& peer_infos,
                                                       const i_image_info_storage& image_info_storage,
                                                       const t_message_info_storage& messages)
    : _peer_infos { peer_infos }
    , _image_info_storage { image_info_storage }
    , _messages { messages }
{
}


const t_peer_infos& t_messenger_context_getter::peer_infos() const {
    return _peer_infos;
}

const i_image_info_storage& t_messenger_context_getter::image_info_storage() const {
    return _image_info_storage;
}

const t_message_info_storage& t_messenger_context_getter::message_info_storage() const {
    return _messages;
}


const t_nickname t_messenger_context_getter::get_peer_nickname(const t_peer_id peer_id) const {
    auto finding_peer_info_predicate = [peer_id](const t_peer_info& peer_info) {
        return peer_id == peer_info._peer_id;
    };

    if (t_peer_infos::iterator it = std::find_if(_peer_infos.begin(), _peer_infos.end(), finding_peer_info_predicate); it != _peer_infos.end()) {
        return it->_nickname;
    }

    throw std::runtime_error { "peer nickname does not exist by peer_id " + peer_id.to_string() };
}

const t_avatar_id t_messenger_context_getter::get_default_avatar_id(const t_peer_id peer_id) const {
    return {};
}

const t_avatar_id t_messenger_context_getter::get_latest_avatar_id(const t_peer_id peer_id) const {
    return _image_info_storage.get_latest_avatar_id(peer_id);
}

} // namespace memory
