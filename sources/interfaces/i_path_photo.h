#ifndef I_PATH_PHOTO_H
#define I_PATH_PHOTO_H

#include "../t_defines.h"

class i_photo_fs_path
{
public:
    virtual ~i_photo_fs_path() = 0;

    virtual t_fs_path get_fs_path_for_photo(const t_peer_id peer) const = 0;

    virtual t_fs_path get_fs_path_for_photo(const t_peer_id peer, const t_fs_filename& filename) const = 0;

    [[maybe_unused]]
    virtual t_fs_path get_fs_path_for_photo(const t_peer_id peer, const t_photo_bundle_id& bundle_id, const t_fs_filename& filename) const = 0;
};

#endif // I_PATH_PHOTO_H
