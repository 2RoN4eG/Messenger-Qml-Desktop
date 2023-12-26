#ifndef I_IMAGE_INFO_STORAGE_H
#define I_IMAGE_INFO_STORAGE_H

#include "../t_image_info.h"

class i_make_path;

class i_image_info_storage
{
public:
    virtual ~i_image_info_storage() = 0;

    // getting image_info by image_id (image_info::path will be maked using avatar_type)
    virtual t_image_info get_image_info(const t_image_id image_id, const i_make_path& path_holder) const = 0;

    // setting image_info by image_id and peer_id
    virtual void set_image_info(const t_peer_id peer_id, const t_image_id image_id, const t_url& url, const t_thumb_hash& thumb_hash) = 0;
};

#endif // I_IMAGE_INFO_STORAGE_H
