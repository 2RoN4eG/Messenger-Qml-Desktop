#ifndef I_PEER_INFO_STORAGE_H
#define I_PEER_INFO_STORAGE_H

#include "../t_defines.h"


class t_peer_info;


class i_set_peer_info
{
public:
    virtual ~i_set_peer_info() = 0;

    virtual void set_peer_info(const t_peer_id peer_id, t_nickname&& nickname) = 0;

    virtual void set_image_info(const t_peer_id peer_id, const t_url& url, const t_thumb_hash& thumb_hash) = 0;
};

#endif // I_PEER_INFO_STORAGE_H
