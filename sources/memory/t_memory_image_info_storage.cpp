#include "t_memory_image_info_storage.h"

#include "../t_path_aggregator.h"


t_image_info_extended::t_image_info_extended(const t_peer_id peer_id, const t_image_id image_id, t_image_info&& image_info)
    : t_image_info_extended { peer_id, image_id, {}, std::move(image_info) }
{
}

t_image_info_extended::t_image_info_extended(const t_peer_id peer_id, const t_image_id image_id, t_photo_bundle_id bundle_id, t_image_info&& image_info)
    : _peer_id { peer_id }
    , _image_id { image_id }
    , _bundle_id { bundle_id }
    , _image_info { std::move(image_info) }
{
}

bool operator<(const t_image_info_extended& lhs, const t_image_info_extended& rhs) {
    return lhs._image_id < rhs._image_id;
}

// t_peer and i_image_path_maker are hidden in constructor becase object will be used by interface

t_image_info t_memory_image_info_storage::get_image_info(const t_image_id image_id, const i_make_path& path_holder) const {
    auto predicate = [this, &image_id](const t_image_info_extended& extended) { return extended._image_id == image_id; };
    if (t_image_infos_iterator it = std::find_if(_image_infos.begin(), _image_infos.end(), predicate); it != _image_infos.end()) {
        t_image_info image_info = it->_image_info;

        const t_fs_filename& filename = image_info._url.fileName().toStdString();

        image_info._path = path_holder(it->_peer_id, filename);

        return image_info;
    }
    throw std::runtime_error { "t_image_info_storage_memory::get_image_info: avatar info does not exist by avatar id { " + image_id.to_string() + " }" };
}

void t_memory_image_info_storage::set_image_info(const t_peer_id peer_id, const t_image_id image_id, const t_url& url, const t_thumb_hash& thumb_hash) {
    _image_infos.emplace(peer_id, image_id, t_image_info { url, thumb_hash });
}
