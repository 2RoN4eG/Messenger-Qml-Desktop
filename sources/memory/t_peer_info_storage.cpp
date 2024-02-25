#include "t_peer_info_storage.h"


namespace memory
{

t_peer_info_storage::t_peer_info_storage(i_image_info_storage &image_info_storage, t_image_id_generator& image_id_generator)
    : _image_info_storage { image_info_storage }
    , _image_id_generator { image_id_generator }
{
}

const t_peer_info& t_peer_info_storage::get_peer_info(const t_peer_id peer_id) const {
    return {};
}

void t_peer_info_storage::set_peer_info(const t_peer_id peer_id, const t_nickname& nickname) {
    // _peer_infos.emplace({ peer_id, nickname });
}

void t_peer_info_storage::set_image_info(const t_peer_id peer_id,  const t_url& url, const t_thumb_hash& thumb_hash) {
    const t_image_id image_id = _image_id_generator.get_value_and_generate_next();

    _image_info_storage.set_image_info(peer_id, image_id, url, thumb_hash);
}

} // namespace memory
