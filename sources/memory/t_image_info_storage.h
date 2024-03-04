#ifndef T_IMAGE_INFO_STORAGE_H
#define T_IMAGE_INFO_STORAGE_H

#include "../t_defines.h"
#include "../t_image_info.h"
#include "../interface/i_image_info_storage.h"

#include <set>


class i_path_maker;

using t_image_infos = std::set<t_image_info>;
using t_image_infos_iterator = t_image_infos::iterator;

namespace memory
{

// Im memory image info storage
// Pros: to avoid working with fs
// Cons: in systems with limited amount of memory needs to use "in file image info storage"

class t_image_info_storage : public i_image_info_storage
{
public:
    virtual ~t_image_info_storage() override = default;


    void set_default_avatar_image_info(const t_peer_id peer_id, const t_avatar_id image_id) override;

    void set_avatar_image_info(const t_peer_id peer_id, const t_avatar_id image_id, const t_url& url, const t_thumb_hash& thumb_hash) override;

    void set_photo_image_info(const t_peer_id peer_id, const t_photo_id photo_id, const t_url& url, const t_thumb_hash& thumb_hash) override;


    // getting image path using image_id and path maker (image_info::path will be maked using avatar_type)
    const t_fs_path get_image_path(const t_image_id image_id, const i_path_maker& path_maker) const override;

    // getting image url using image_id
    const t_url& get_image_url(const t_image_id image_id) const override;

    // getting image thumb hash using image_id
    const t_thumb_hash& get_image_thumb_hash(const t_image_id image_id) const override;

    // getting default avatar id (image id) using peer_id
    const t_image_id get_default_avatar_id(const t_peer_id peer_id) const override;

    // getting lates avatar id (image id) using peer_id
    const t_image_id get_latest_avatar_id(const t_peer_id peer_id) const override;

protected:
    t_image_infos _image_infos;
};

}

#endif // T_IMAGE_INFO_STORAGE_H
