#ifndef T_MEMORY_META_HOLDER_H
#define T_MEMORY_META_HOLDER_H

#include "../t_defines.h"

#include "../interface/i_meta_holder.h"
#include "../interface/i_rotator.h"

#include <set>

class t_fs;
class t_fs_meta;

using t_meta_holder_cache = std::set<t_fs_path>;

struct t_size_range {
    t_fs_size _minimum {};
    t_fs_size _maximum {};
};

// alternative name is { t_path_holder }
class t_memory_meta_holder : public i_meta_holder, public i_rotator
{
public:
    t_memory_meta_holder(t_fs_size minimum_capacity, t_fs_size maximum_capacity, t_meta_holder_cache&& paths);

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
    t_size_range _range;

    t_meta_holder_cache _cache;

    std::vector<t_fs_path> _to_remove;
};

#endif // T_MEMORY_META_HOLDER_H
