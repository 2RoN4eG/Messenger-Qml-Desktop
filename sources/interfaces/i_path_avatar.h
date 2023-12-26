#ifndef I_PATH_AVATAR_H
#define I_PATH_AVATAR_H

#include "../t_defines.h"

class i_avatar_fs_path
{
public:
    virtual ~i_avatar_fs_path() = 0;

    virtual t_fs_path get_fs_path_for_avatar(const t_peer_id peer) const = 0;

    virtual t_fs_path get_fs_path_for_avatar(const t_peer_id peer, const t_avatar_type_id avatar_type) const = 0;

    virtual t_fs_path get_fs_path_for_avatar(const t_peer_id peer, const t_avatar_type_id avatar_type, const t_fs_filename& filename) const = 0;
};

#endif // I_PATH_AVATAR_H
