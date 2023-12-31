#include "t_image_info_storage_memory.h"

#include "t_path_aggregator.h"

//

t_image_info_extended::t_image_info_extended(const t_image_id avatar_id, const t_peer_id peer_id, t_image_info&& avatar_info)
    : _image_id { avatar_id }
    , _peer_id { peer_id }
    , _image_info { std::move(avatar_info) }
{
}

bool operator<(const t_image_info_extended& lhs, const t_image_info_extended& rhs) {
    return lhs._image_id < rhs._image_id;
}

// t_peer and i_image_path_maker are hidden in constructor becase object will be used by interface
t_image_info_storage_memory::t_image_info_storage_memory()
{
}

t_image_info t_image_info_storage_memory::get_image_info(const t_image_id image_id, const i_path_holder& path_holder) const {
    auto predicate = [this, &image_id](const t_image_info_extended& extended) { return extended._image_id == image_id; };
    if (t_image_infos_iterator it = std::find_if(_image_infos.begin(), _image_infos.end(), predicate); it != _image_infos.end()) {
        t_image_info image_info = it->_image_info;
        const t_fs_filename& filename = image_info._url.fileName().toStdString();
        image_info._path = path_holder(it->_peer_id, filename);

        std::cout << "avatar_id { " << image_id.to_string() << " } contains info {"
                  << " url: " << image_info._url.toString().toStdString()
                  << ", thumb_hash: " << image_info._thumb_hash
                  << ", path: " << image_info._path << " }"
                  << std::endl;
        return image_info;
    }
    throw std::runtime_error { "t_image_info_storage_memory::get_image_info: avatar info does not exist by avatar id { " + image_id.to_string() + " }" };
}

void t_image_info_storage_memory::set_image_info(const t_image_id image_id, const t_peer_id peer_id, const t_url& url, const t_thumb_hash& thumb_hash) {
    _image_infos.emplace(image_id, peer_id, t_image_info { url, thumb_hash });
}
