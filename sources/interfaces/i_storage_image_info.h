#ifndef I_STORAGE_IMAGE_INFO_H
#define I_STORAGE_IMAGE_INFO_H

#include "../t_defines.h"

class i_image_fs_path_maker;

class i_image_info_storage
{
public:
    virtual ~i_image_info_storage() = 0;


    virtual void set_default_avatar_image_info(const t_peer_id peer_id, const t_avatar_id image_id) = 0;

    // setting avatar info { url, thumb_hash } by t_peer_id and t_avatar_id
    virtual void set_avatar_image_info(const t_peer_id peer_id, const t_avatar_id avatar_id, const t_url& url, const t_thumb_hash& thumb_hash) = 0;

    // setting photo info { url, thumb_hash } by t_peer_id and t_photo_id
    virtual void set_photo_image_info(const t_peer_id peer_id, const t_photo_id photo_id, const t_url& url, const t_thumb_hash& thumb_hash) = 0;


    // getting image path using image_id and path maker (image_info::path will be maked using avatar_type)
    virtual const t_fs_path get_image_fs_path(const t_image_id image_id, const i_image_fs_path_maker& path_maker) const = 0;

    // getting image url using image_id
    virtual const t_url& get_image_url(const t_image_id image_id) const = 0;

    // getting image thumb hash using image_id
    virtual const t_thumb_hash& get_image_thumb_hash(const t_image_id image_id) const = 0;


    //
    virtual const t_image_id get_default_avatar_id(const t_peer_id peer_id) const = 0;

    //
    virtual const t_image_id get_latest_avatar_id(const t_peer_id peer_id) const = 0;
};

#endif // I_STORAGE_IMAGE_INFO_H
