#ifndef T_META_HOLDER_MEMORY_H
#define T_META_HOLDER_MEMORY_H

#include "t_defines.h"

#include <set>

class t_fs;
class t_fs_meta;

// alternative name is { i_cache_holder }
class i_meta_holder {
public:
    virtual bool does_exist(const t_fs_path& path) const = 0;

    virtual void do_hold(const t_fs_path& path) = 0;

    virtual void do_register(const t_fs_path& path) = 0;

    virtual void do_unregister(const t_fs_path& path) = 0;
};

class i_rotator {
public:
    virtual void do_rotate(const t_fs& fs) = 0;
};

using t_cache = std::set<t_fs_path>;

struct t_range {
    t_fs_size _minimum {};
    t_fs_size _maximum {};
};

// alternative name is { t_path_holder }
class t_meta_holder_memory : public i_meta_holder, public i_rotator
{
public:
    t_meta_holder_memory(t_fs_size minimum_capacity, t_fs_size maximum_capacity, t_cache&& paths);

    // implement i_meta_holder interface

    bool does_exist(const t_fs_path& path) const override;

    void do_register(const t_fs_path& path) override;

    // const time (O(1))
    void do_hold(const t_fs_path& path) override {
        do_register(path);
    }

    void do_unregister(const t_fs_path& path) override;

    // implement i_rotator interface

    void do_rotate(const t_fs& fs) override;

protected:
    bool _does_exist(const t_fs_path& path) const;

    void _do_register(const t_fs_path& path);

    void _do_unregister(const t_fs_path& path);

    void _do_unregister_out_of_range(const t_fs& fs);

protected:
    t_range _range;

    t_cache _cache;

    std::vector<t_fs_path> _to_remove;
};

#endif // T_META_HOLDER_MEMORY_H
