#ifndef I_META_HOLDER_H
#define I_META_HOLDER_H

#include "../t_defines.h"

// alternative name is { i_cache_holder }
class i_meta_holder {
public:
    virtual ~i_meta_holder() = 0;

    virtual bool does_exist(const t_fs_path& path) const = 0;

    virtual void do_hold(const t_fs_path& path) = 0;

    virtual void do_register(const t_fs_path& path) = 0;

    virtual void do_unregister(const t_fs_path& path) = 0;
};

#endif // I_META_HOLDER_H
