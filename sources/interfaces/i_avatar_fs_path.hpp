#pragma once

#include "../t_defines.h"

class i_avatar_fs_path
{
public:
    virtual ~i_avatar_fs_path() = 0;

    virtual t_fs_path get_avatar_fs_path(const t_peer_id peer) const = 0;

    virtual t_fs_path get_avatar_fs_path(const t_peer_id peer, const t_avatar_type_id avatar_type) const = 0;

    virtual t_fs_path get_avatar_fs_path(const t_peer_id peer, const t_avatar_type_id avatar_type, const t_fs_filename& filename) const = 0;
};
