#ifndef T_MEMORY_IMAGE_INFO_STORAGE_H
#define T_MEMORY_IMAGE_INFO_STORAGE_H

#include "../t_defines.h"
#include "../t_image_info.h"
#include "../interface/i_image_info_storage.h"

#include <set>

//

class i_make_path;

using t_extended_image_infos = std::set<t_image_info_extended>;
using t_image_infos_iterator = t_extended_image_infos::iterator;

//

class t_memory_image_info_storage : public i_image_info_storage
{
public:
    t_image_info get_image_info(const t_image_id image_id, const i_make_path& path_holder) const override;

    void set_image_info(const t_peer_id peer_id, const t_image_id image_id, const t_url& url, const t_thumb_hash& thumb_hash) override;

protected:
    t_extended_image_infos _image_infos;
};

#endif // T_MEMORY_IMAGE_INFO_STORAGE_H
