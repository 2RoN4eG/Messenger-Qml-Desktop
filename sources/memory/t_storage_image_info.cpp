#include "t_storage_image_info.h"

#include "../t_path_aggregator.h"


// Слой для балансировки разных типов изображений: в случае необходимости, мы
// можем добавлять новые контейнеры для однотипных объектов если будет просадка
// по производительности

// t_peer and i_image_path_maker are hidden in constructor becase object will be used by interface

namespace
{
    struct t_finding_image_info_by_image_id
    {
        t_finding_image_info_by_image_id(const t_image_id image_id)
            : _image_id { image_id }
        {
        }

        bool operator()(const t_image_info& image_info) const {
            return image_info._image_id == _image_id;
        }

        const t_image_id _image_id;
    };

    struct t_finding_image_info_by_image_id_and_image_type_id
    {
        t_finding_image_info_by_image_id_and_image_type_id(const t_image_id image_id, const t_image_type_id image_type_id)
            : _image_id { image_id }
            , _image_type_id { image_type_id }
        {
        }

        bool operator()(const t_image_info& image_info) const
        {
            return image_info._image_id == _image_id && image_info._image_type_id == _image_type_id;
        }

        const t_image_id _image_id;

        const t_image_type_id _image_type_id;
    };

    struct t_finding_image_info_by_peer_id_and_image_type_id
    {
        t_finding_image_info_by_peer_id_and_image_type_id(const t_peer_id peer_id, const t_image_type_id image_type_id)
            : _peer_id { peer_id }
            , _image_type_id { image_type_id }
        {
        }

        bool operator()(const t_image_info& image_info) const
        {
            return image_info._peer_id == _peer_id && image_info._image_type_id == _image_type_id;
        }

        const t_peer_id _peer_id;

        const t_image_type_id _image_type_id;
    };

    inline const t_image_info& get_image_info_by_image_id(const t_image_infos& image_infos,
                                                          const t_image_id image_id)
    {
        const t_finding_image_info_by_image_id finding_predicate { image_id };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(), std::move(finding_predicate)); it != image_infos.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_image_info_by_image_id: image info does not exist by image_id { " + image_id.to_string() + " }" };
    }

    inline const t_image_info& get_avatar_info_by_avatar_id(const t_image_infos& image_infos,
                                                            const t_avatar_id avatar_id)
    {
        const t_finding_image_info_by_image_id_and_image_type_id finding_predicate { avatar_id, t_image_type_id::t_squared_avatar_image };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(), std::move(finding_predicate)); it != image_infos.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_avatar_info_by_avatar_id: avatar info does not exist by avatar_id { " + avatar_id.to_string() + " }" };
    }

    inline const t_image_info& get_photo_info_by_photo_id(const t_image_infos& image_infos,
                                                          const t_photo_id photo_id)
    {
        const t_finding_image_info_by_image_id_and_image_type_id finding_predicate { photo_id, t_image_type_id::t_photo_image };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(), std::move(finding_predicate)); it != image_infos.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_photo_info_by_photo_id: photo info does not exist by photo_id { " + photo_id.to_string() + " }" };
    }

    inline const t_image_info& get_avatar_info_by_peer_id_and_image_type_id(const t_image_infos& image_infos,
                                                                            const t_peer_id peer_id,
                                                                            const t_image_type_id image_type_id)
    {
        const t_finding_image_info_by_peer_id_and_image_type_id finding_predicate { peer_id, image_type_id };

        if (t_image_infos_iterator it = std::find_if(image_infos.begin(), image_infos.end(), std::move(finding_predicate)); it != image_infos.end())
        {
            return *it;
        }

        throw std::runtime_error {
            "get_avatar_info_by_peer_id_and_image_type_id: "
            "image info does not exist by"
            " peer_id { " + peer_id.to_string() + " } and image_type_id { " + image_type_id_to_string(image_type_id) + " }"
        };
    }

    inline t_fs_filename get_fs_filename(const t_url& url)
    {
        return url.fileName().toStdString();
    }

    inline void _print_image_info(const t_image_info& image_info)
    {
        std::cout << "peer_id: "         << image_info._peer_id << ", "
                  << "image_id: "        << image_info._image_id << ", "
                  << "image_type_id: "   << image_type_id_to_string(image_info._image_type_id) << ", "
                  << "image_bundle_id: " << image_info._image_bundle_id << ", "
                  << "url: "             << image_info._url.toString().toStdString() << ", "
                  << "thumb_hash: "      << "" << ", "
                  << std::endl;
    }
}

namespace memory
{
    t_image_info_storage::t_image_info_storage(t_image_infos& image_infos)
        : _image_infos { image_infos }
    {
    }

    void t_image_info_storage::set_default_avatar_image_info(const t_peer_id peer_id, const t_avatar_id avatar_id)
    {
        const std::string default_avatar_filename { peer_id.to_string() + ".jpg" };

        _image_infos.emplace(peer_id, avatar_id, t_image_type_id::t_default_avatar_image, t_url { default_avatar_filename.c_str() }, t_thumb_hash {});
    }

    void t_image_info_storage::set_avatar_image_info(const t_peer_id peer_id, const t_avatar_id avatar_id, const t_url& url, const t_thumb_hash& thumb_hash)
    {
        _image_infos.emplace(peer_id, avatar_id, t_image_type_id::t_squared_avatar_image, url, thumb_hash);
    }

    void t_image_info_storage::set_photo_image_info(const t_peer_id peer_id, const t_photo_id photo_id, const t_url& url, const t_thumb_hash& thumb_hash)
    {
        _image_infos.emplace(peer_id, photo_id, t_image_type_id::t_photo_image, url, thumb_hash);
    }

    const t_fs_path t_image_info_storage::get_image_fs_path(const t_image_id image_id, const i_image_fs_path_maker& make_path) const
    {
        const t_image_info& image_info = get_image_info_by_image_id(_image_infos, image_id);

        const t_fs_filename& filename = get_fs_filename(image_info._url);

        return make_path(image_info._peer_id, filename);
    }

    const t_url& t_image_info_storage::get_image_url(const t_image_id image_id) const
    {
        const t_image_info& image_info = get_image_info_by_image_id(_image_infos, image_id);

        return image_info._url;
    }

    const t_thumb_hash& t_image_info_storage::get_image_thumb_hash(const t_image_id image_id) const
    {
        const t_image_info& image_info = get_image_info_by_image_id(_image_infos, image_id);

        return image_info._thumb_hash;
    }

    const t_image_id t_image_info_storage::get_default_avatar_id(const t_peer_id peer_id) const
    {
        const t_image_info& image_info = get_avatar_info_by_peer_id_and_image_type_id(_image_infos, peer_id, t_image_type_id::t_default_avatar_image);

        return image_info._image_id;
    }

    const t_image_id t_image_info_storage::get_latest_avatar_id(const t_peer_id peer_id) const
    {
        const t_image_info& image_info = get_avatar_info_by_peer_id_and_image_type_id(_image_infos, peer_id, t_image_type_id::t_squared_avatar_image);

        return image_info._image_id;
    }
}
