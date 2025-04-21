#ifndef I_PATH_SELF_AND_PEER_H
#define I_PATH_SELF_AND_PEER_H

#include "../t_defines.h"

class i_peer_fs_path
{
public:
    virtual ~i_peer_fs_path() = 0;

    virtual const t_fs_path get_self_fs_path() const = 0;

    virtual const t_fs_path get_peer_fs_path(const t_peer_id peer) const = 0;
};

#endif // I_PATH_SELF_AND_PEER_H
