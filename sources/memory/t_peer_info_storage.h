#ifndef T_PEER_INFO_STORAGE_H
#define T_PEER_INFO_STORAGE_H

#include "../t_defines.h"
#include "../t_image_info.h"
#include "../interface/i_image_info_storage.h"
#include "../interface/i_peer_info_storage.h"

#include <set>


using t_peer_infos = std::set<t_peer_info>;
using t_avatar = t_json_avatar_model;
using t_avatars = std::vector<t_avatar>;

namespace memory
{

class t_peer_info_storage : public i_peer_info_storage
{
public:
    t_peer_info_storage(i_image_info_storage& image_info_storage, t_image_id_generator& image_id_generator);

    void set_peer_info(const t_peer_id peer_id, const t_nickname& nickname) override;

    const t_peer_info& get_peer_info(const t_peer_id peer_id) const override;

    void set_image_info(const t_peer_id peer_id, const t_url& url, const t_thumb_hash& thumb_hash);

protected:
    t_peer_infos _peer_infos;

    i_image_info_storage& _image_info_storage;

    t_image_id_generator& _image_id_generator;
};

} // namespace memory

#endif // T_PEER_INFO_STORAGE_H
