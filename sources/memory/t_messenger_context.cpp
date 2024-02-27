#include "t_messenger_context.h"

#include <iostream>


namespace memory
{

t_peer_info_context::t_peer_info_context(t_peer_infos& peer_infos, i_image_info_storage& image_info_storage, t_image_id_generator& image_id_generator)
    : _peer_infos { peer_infos }
    , _image_info_storage { image_info_storage }
    , _image_id_generator { image_id_generator }
{
}

void t_peer_info_context::set_peer_info(const t_peer_id peer_id, t_nickname&& nickname) {
    // std::cout << "peer_id: " << peer_id << ", nickname: " << nickname << std::endl;

    _peer_infos.emplace(t_peer_info { peer_id, std::move(nickname) });
}

void t_peer_info_context::set_image_info(const t_peer_id peer_id,  const t_url& url, const t_thumb_hash& thumb_hash) {
    const t_image_id image_id = _image_id_generator.get_value_and_generate_next();

    _image_info_storage.set_image_info(peer_id, image_id, url, thumb_hash);
}

t_avatar_id t_peer_info_context::get_latest_avatar_id(const t_peer_id peer_id) const {
    return _image_info_storage.get_latest_avatar_id(peer_id);
}

} // namespace memory
