#ifndef I_STORAGE_PEER_INFO_H
#define I_STORAGE_PEER_INFO_H

#include "../t_defines.h"

class i_peer_info_storage
{
public:
    virtual ~i_peer_info_storage() = 0;


    virtual void set_peer_info(const t_peer_id peer_id, t_nickname&& nickname) = 0;


    virtual t_nickname get_nickname(const t_peer_id peer_id) const = 0;


    virtual const t_peer_infos& get_peer_infos() const = 0;


    virtual const size_t size() const = 0;

    virtual const t_peer_id operator[](size_t index) const = 0;
};

#endif // I_STORAGE_PEER_INFO_H
