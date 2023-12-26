#ifndef T_IMAGE_INFO_STORAGE_MEMORY_H
#define T_IMAGE_INFO_STORAGE_MEMORY_H

#include "t_defines.h"
#include "t_image_info.h"

#include <set>

//

class i_path_holder;

//

class i_image_info_storage {
public:
    // getting image_info by image_id (image_info::path will be maked using avatar_type)
    virtual t_image_info get_image_info(const t_image_id image_id, const i_path_holder& path_holder) const = 0;

    // setting image_info by image_id
    virtual void set_image_info(const t_image_id image_id, const t_peer peer, const t_url& url, const t_thumb_hash& thumb_hash) = 0;
};

//

using t_image_info_extendeds = std::set<t_image_info_extended>;

using t_image_infos_iterator = t_image_info_extendeds::iterator;

//

class t_image_info_storage_memory : public i_image_info_storage {
public:
    t_image_info_storage_memory();

    t_image_info get_image_info(const t_image_id image_id, const i_path_holder& path_holder) const override;

    void set_image_info(const t_image_id image_id, const t_peer peer, const t_url& url, const t_thumb_hash& thumb_hash) override;

protected:
    t_image_info_extendeds _image_infos;
};

#endif // T_IMAGE_INFO_STORAGE_MEMORY_H
