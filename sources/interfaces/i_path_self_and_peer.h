#ifndef I_PATH_SELF_AND_PEER_H
#define I_PATH_SELF_AND_PEER_H

#include "../t_defines.h"

class i_path_self_path_and_peer
{
public:
    virtual ~i_path_self_path_and_peer() = 0;

    virtual t_fs_path get_fs_path_for_self() const = 0;

    virtual t_fs_path get_fs_path_for_peer(const t_peer_id peer) const = 0;
};

#endif // I_PATH_SELF_AND_PEER_H
