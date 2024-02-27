#include "t_image_info_storage.h"

#include "../t_path_aggregator.h"
#include <iostream>

#include <QDebug>

// t_peer and i_image_path_maker are hidden in constructor becase object will be used by interface

namespace {
const t_image_info_extended& get_extended_image_info(const t_extended_image_infos& image_infos, const t_image_id image_id) {
    auto finding_predicate = [image_id](const t_image_info_extended& extended) {
        return extended._image_id == image_id;
    };

    if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(),  finding_predicate); it != image_infos.end()) {
        return *it;
    }

    throw std::runtime_error { "t_image_info_storage_memory::get_image_info: avatar info does not exist by avatar id { " + image_id.to_string() + " }" };
}

const t_image_info_extended& get_extended_image_info(const t_extended_image_infos& image_infos, const t_peer_id peer_id) {
    auto finding_predicate = [peer_id](const t_image_info_extended& extended) {
        return extended._peer_id == peer_id;
    };

    if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(),  finding_predicate); it != image_infos.end()) {
        return *it;
    }

    throw std::runtime_error { "t_image_info_storage_memory::get_image_info: avatar info does not exist by peer id { " + peer_id.to_string() + " }" };
}
}

namespace memory
{

const t_fs_path t_image_info_storage::get_image_path(const t_image_id image_id, const i_path_maker& path_maker) const {
    const t_image_info_extended& image_info_extended = get_extended_image_info(_image_infos, image_id);

    const t_fs_filename& filename = image_info_extended._url.fileName().toStdString();

    return path_maker(image_info_extended._peer_id, filename);
}

const t_url& t_image_info_storage::get_image_url(const t_image_id image_id) const {
    const t_image_info_extended& image_info_extended = get_extended_image_info(_image_infos, image_id);

    qDebug() << "URL: " << image_info_extended._url;

    return image_info_extended._url;
}

const t_thumb_hash& t_image_info_storage::get_image_thumb_hash(const t_image_id image_id) const {
    const t_image_info_extended& image_info_extended = get_extended_image_info(_image_infos, image_id);

    return image_info_extended._thumb_hash;
}

const t_image_id t_image_info_storage::get_latest_avatar_id(const t_peer_id peer_id) const {
    const t_image_info_extended& image_info_extended = get_extended_image_info(_image_infos, peer_id);

    return image_info_extended._image_id;
}

void t_image_info_storage::set_image_info(const t_peer_id peer_id, const t_image_id image_id, const t_url& url, const t_thumb_hash& thumb_hash) {
    // std::cout << "set_image_info ("
    //           << "peer_id: " << peer_id << ", "
    //           << "image_id: " << image_id << ", "
    //           << "url: " << url.toString().toStdString() << ", "
    //           << "t_thumb_hash" << thumb_hash
    //           << ")" << std::endl;

    _image_infos.emplace(peer_id, image_id, t_image_info { url, thumb_hash });
}

}
