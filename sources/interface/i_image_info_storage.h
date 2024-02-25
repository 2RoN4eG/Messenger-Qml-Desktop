#ifndef I_IMAGE_INFO_STORAGE_H
#define I_IMAGE_INFO_STORAGE_H

#include "../t_image_info.h"

class i_path_maker;

class i_image_info_storage
{
    // TODO: Replace get_image_info by get_image_path(), get_image_url(), get_image_thumb_hash()

public:
    virtual ~i_image_info_storage() = 0;

    // setting image_info by image_id and peer_id
    virtual void set_image_info(const t_peer_id peer_id, const t_image_id image_id, const t_url& url, const t_thumb_hash& thumb_hash) = 0;

    // getting image path using image_id and path maker (image_info::path will be maked using avatar_type)
    virtual const t_fs_path get_image_path(const t_image_id image_id, const i_path_maker& path_maker) const = 0;

    // getting image url using image_id
    virtual const t_url& get_image_url(const t_image_id image_id) const = 0;

    // getting image thumb hash using image_id
    virtual const t_thumb_hash& get_image_thumb_hash(const t_image_id image_id) const = 0;
};

#endif // I_IMAGE_INFO_STORAGE_H
