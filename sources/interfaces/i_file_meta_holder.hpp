#ifndef i_file_meta_holder_H
#define i_file_meta_holder_H

#include "../t_defines.h"

// alternative name is { i_cache_holder }
class i_file_meta_holder
{
public:
    virtual ~i_file_meta_holder() = 0;

    virtual bool does_path_exist(const t_fs_path& path) const = 0;

    virtual void hold_on(const t_fs_path& path) = 0;

    virtual void do_register(const t_fs_path& path) = 0;

    virtual void do_unregister(const t_fs_path& path) = 0;
};

#endif // i_file_meta_holder_H
