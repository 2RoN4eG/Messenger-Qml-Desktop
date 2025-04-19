#include "t_image_component_storage.hpp"

#include "../t_path_aggregator.h"


// Слой для балансировки разных типов изображений: в случае необходимости, мы
// можем добавлять новые контейнеры для однотипных объектов если будет просадка
// по производительности

// t_peer and i_image_path_maker are hidden in constructor becase object will be used by interface

namespace
{
    struct t_finding_image_component_by_image_id
    {
        t_finding_image_component_by_image_id(const t_image_id image_id)
            : _image_id { image_id }
        {
        }

        bool operator()(const t_image_component& image_component) const
        {
            return image_component._image_id == _image_id;
        }

        const t_image_id _image_id;
    };

    struct t_finding_image_component_by_image_id_and_image_type_id
    {
        t_finding_image_component_by_image_id_and_image_type_id(const t_image_id image_id, const t_image_type_id image_type_id)
            : _image_id { image_id }
            , _image_type_id { image_type_id }
        {
        }

        bool operator()(const t_image_component& image_component) const
        {
            return image_component._image_id == _image_id && image_component._image_type_id == _image_type_id;
        }

        const t_image_type_id _image_type_id;

        const t_image_id _image_id;
    };

    struct t_finding_image_component_by_peer_id_and_image_type_id
    {
        t_finding_image_component_by_peer_id_and_image_type_id(const t_peer_id peer_id, const t_image_type_id image_type_id)
            : _peer_id { peer_id }
            , _image_type_id { image_type_id }
        {
        }

        bool operator()(const t_image_component& image_component) const
        {
            return image_component._peer_id == _peer_id && image_component._image_type_id == _image_type_id;
        }

        const t_peer_id _peer_id;

        const t_image_type_id _image_type_id;
    };


    inline const t_image_component& get_image_component_by_image_id(const t_image_components& image_components, const t_image_id image_id)
    {
        const t_finding_image_component_by_image_id finding_predicate { image_id };

        if (t_image_components_iterator it = std::find_if(image_components.begin(), image_components.end(), std::move(finding_predicate)); it != image_components.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_image_component_by_image_id: image component does not exist, image_id is " + image_id.to_string() };
    }

    inline const t_image_component& get_avatar_component_by_avatar_id(const t_image_components& image_components, const t_avatar_id avatar_id)
    {
        const t_finding_image_component_by_image_id_and_image_type_id finding_predicate { avatar_id, t_image_type_id::t_squared_avatar };

        if (t_image_components_iterator it = std::find_if(image_components.begin(), image_components.end(), std::move(finding_predicate)); it != image_components.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_avatar_component_by_avatar_id: avatar component does not exist, avatar_id is " + avatar_id.to_string() };
    }

    inline const t_image_component& get_photo_component_by_photo_id(const t_image_components& image_components, const t_photo_id photo_id)
    {
        const t_finding_image_component_by_image_id_and_image_type_id finding_predicate { photo_id, t_image_type_id::t_photo };

        if (t_image_components_iterator it = std::find_if(image_components.begin(), image_components.end(), std::move(finding_predicate)); it != image_components.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_photo_component_by_photo_id: photo component does not exist, photo_id is " + photo_id.to_string() };
    }

    inline const t_image_component& get_avatar_component_by_peer_id_and_image_type_id(const t_image_components& image_components, const t_peer_id peer_id, const t_image_type_id image_type_id)
    {
        const t_finding_image_component_by_peer_id_and_image_type_id finding_predicate { peer_id, image_type_id };

        if (t_image_components_iterator it = std::find_if(image_components.begin(), image_components.end(), std::move(finding_predicate)); it != image_components.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_avatar_component_by_peer_id_and_image_type_id: image component does not exist, peer_id is " + peer_id.to_string() + ", image_type_id is " + image_type_id_to_string(image_type_id) };
    }

    inline t_fs_filename get_fs_filename(const t_url& url)
    {
        return url.fileName().toStdString();
    }

    inline void _print_image_component(const t_image_component& image_component)
    {
        std::cout << "peer_id: "         << image_component._peer_id << ", "
                  << "image_id: "        << image_component._image_id << ", "
                  << "image_type_id: "   << image_type_id_to_string(image_component._image_type_id) << ", "
                  << "image_bundle_id: " << image_component._image_bundle_id << ", "
                  << "url: "             << image_component._url.toString().toStdString() << ", "
                  << "thumb_hash: "      << "" << ", "
                  << std::endl;
    }
}

namespace memory
{
    t_image_component_storage::t_image_component_storage(t_image_components& image_components)
        : _image_components { image_components }
    {
    }

    void t_image_component_storage::set_default_avatar_component(const t_peer_id peer_id, const t_avatar_id avatar_id)
    {
        const std::string default_avatar_filename { peer_id.to_string() + ".jpg" };

        _image_components.emplace(peer_id, avatar_id, t_image_type_id::t_default_avatar, t_url { default_avatar_filename.c_str() }, t_thumb_hash {});
    }

    void t_image_component_storage::set_avatar_component(const t_peer_id peer_id, const t_avatar_id avatar_id, const t_url& url, const t_thumb_hash& thumb_hash)
    {
        _image_components.emplace(peer_id, avatar_id, t_image_type_id::t_squared_avatar, url, thumb_hash);
    }

    void t_image_component_storage::set_photo_component(const t_peer_id peer_id, const t_photo_id photo_id, const t_url& url, const t_thumb_hash& thumb_hash)
    {
        _image_components.emplace(peer_id, photo_id, t_image_type_id::t_photo, url, thumb_hash);
    }


    const t_fs_path t_image_component_storage::get_image_fs_path(const i_image_fs_path_maker& path_maker, const t_image_id image_id) const
    {
        const t_image_component& image_component = get_image_component_by_image_id(_image_components, image_id);

        const t_fs_filename& filename = get_fs_filename(image_component._url);

        return path_maker(image_component._peer_id, filename);
    }

    const t_url& t_image_component_storage::get_image_url(const t_image_id image_id) const
    {
        const t_image_component& image_component = get_image_component_by_image_id(_image_components, image_id);

        return image_component._url;
    }

    const t_thumb_hash& t_image_component_storage::get_image_thumb_hash(const t_image_id image_id) const
    {
        const t_image_component& image_component = get_image_component_by_image_id(_image_components, image_id);

        return image_component._thumb_hash;
    }


    const bool t_image_component_storage::does_latest_avatar_exist(const t_peer_id peer_id) const
    {
        return {};
    }

    const t_image_id t_image_component_storage::get_default_avatar_id(const t_peer_id peer_id) const
    {
        const t_image_component& image_component = get_avatar_component_by_peer_id_and_image_type_id(_image_components, peer_id, t_image_type_id::t_default_avatar);

        return image_component._image_id;
    }

    const t_image_id t_image_component_storage::get_latest_avatar_id(const t_peer_id peer_id) const
    {
        const t_image_component& image_component = get_avatar_component_by_peer_id_and_image_type_id(_image_components, peer_id, t_image_type_id::t_squared_avatar);

        return image_component._image_id;
    }
}
