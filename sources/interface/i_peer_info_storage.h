#ifndef I_PEER_INFO_STORAGE_H
#define I_PEER_INFO_STORAGE_H

#include "../t_defines.h"

class t_json_peer_info_model;
using t_peer_info = t_json_peer_info_model;

class i_peer_info_storage
{
public:
    virtual ~i_peer_info_storage() = 0;

    virtual const t_peer_info& get_peer_info(const t_peer_id peer_id) const = 0;

    virtual void set_peer_info(const t_peer_id peer_id, const t_nickname& nickname) = 0;
};

#endif // I_PEER_INFO_STORAGE_H
