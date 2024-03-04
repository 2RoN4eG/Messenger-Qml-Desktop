#include "t_image_info_storage.h"

#include "../t_path_aggregator.h"

#include <iostream>

#include <QDebug>


// t_peer and i_image_path_maker are hidden in constructor becase object will be used by interface

namespace {
    const t_image_info& get_image_info_by_image_id(const t_image_infos& image_infos, const t_image_id image_id) {
        auto finding_image_predicate = [image_id](const t_image_info& image_info) {
            return image_id == image_info._image_id;
        };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(), finding_image_predicate); it != image_infos.end()) {
            return *it;
        }

        throw std::runtime_error { "get_image_info_by_image_id: image info does not exist by image_id { " + image_id.to_string() + " }" };
    }

    const t_image_info& get_avatar_info_by_avatar_id(const t_image_infos& image_infos, const t_avatar_id avatar_id) {
        auto finding_avatar_predicate = [avatar_id](const t_image_info& image_info) {
            return avatar_id == image_info._image_id && image_info._image_type == t_image_type::t_avatar_image;
        };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(), finding_avatar_predicate); it != image_infos.end()) {
            return *it;
        }

        throw std::runtime_error { "get_avatar_info_by_avatar_id: avatar info does not exist by avatar_id { " + avatar_id.to_string() + " }" };
    }

    const t_image_info& get_photo_info_by_photo_id(const t_image_infos& image_infos, const t_photo_id photo_id) {
        auto finding_photo_predicate = [photo_id](const t_image_info& image_info) {
            return photo_id == image_info._image_id && image_info._image_type == t_image_type::t_photo_image;
        };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(), finding_photo_predicate); it != image_infos.end()) {
            return *it;
        }

        throw std::runtime_error { "get_photo_info_by_photo_id: photo info does not exist by photo_id { " + photo_id.to_string() + " }" };
    }

    const t_image_info& get_avatar_info_by_peer_id(const t_image_infos& image_infos, const t_peer_id peer_id, const t_image_type image_type) {
        auto finding_avatar_predicate = [peer_id, image_type](const t_image_info& image_info) {
            return peer_id == image_info._peer_id && image_info._image_type == image_type;
        };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(),  finding_avatar_predicate); it != image_infos.end()) {
            return *it;
        }

        throw std::runtime_error { "get_avatar_info_by_peer_id: image info does not exist by peer_id { " + peer_id.to_string() + " }" };
    }
}


namespace memory {
    void t_image_info_storage::set_default_avatar_image_info(const t_peer_id peer_id, const t_avatar_id image_id) {
    }

    void t_image_info_storage::set_avatar_image_info(const t_peer_id peer_id, const t_avatar_id avatar_id, const t_url& url, const t_thumb_hash& thumb_hash) {
        _image_infos.emplace(peer_id, avatar_id, t_image_type::t_avatar_image, url, thumb_hash);
    }

    void t_image_info_storage::set_photo_image_info(const t_peer_id peer_id, const t_photo_id photo_id, const t_url& url, const t_thumb_hash& thumb_hash) {
        _image_infos.emplace(peer_id, photo_id, t_image_type::t_photo_image, url, thumb_hash);
    }


    const t_fs_path t_image_info_storage::get_image_path(const t_image_id image_id, const i_path_maker& path_maker) const {
        const t_image_info& image_info = get_image_info_by_image_id(_image_infos, image_id);

        const t_fs_filename& filename = image_info._url.fileName().toStdString();

        return path_maker(image_info._peer_id, filename);
    }

    const t_url& t_image_info_storage::get_image_url(const t_image_id image_id) const {
        const t_image_info& image_info = get_image_info_by_image_id(_image_infos, image_id);

        return image_info._url;
    }

    const t_thumb_hash& t_image_info_storage::get_image_thumb_hash(const t_image_id image_id) const {
        const t_image_info& image_info = get_image_info_by_image_id(_image_infos, image_id);

        return image_info._thumb_hash;
    }


    const t_image_id t_image_info_storage::get_default_avatar_id(const t_peer_id peer_id) const {
        return {};
    }

    const t_image_id t_image_info_storage::get_latest_avatar_id(const t_peer_id peer_id) const {
        const t_image_info& image_info = get_avatar_info_by_peer_id(_image_infos, peer_id, t_image_type::t_avatar_image);

        return image_info._image_id;
    }
}
