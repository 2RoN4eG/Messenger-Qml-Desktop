#ifndef T_META_HOLDER_H
#define T_META_HOLDER_H

#include "../t_defines.h"

#include "../interfaces/i_meta_holder.h"
#include "../interfaces/i_rotator.h"

#include <set>

class t_fs;
class t_fs_meta;

using t_meta_holder_cache = std::set<t_fs_path>;
using t_capacity = t_fs_size;

struct t_capacity_range
{
    t_capacity _minimum {};
    t_capacity _maximum {};
};

namespace memory
{
    // Im memory meta holder
    // Pros: to avoid working with fs
    // Cons: in systems with limited amount of memory needs to use "in file image info storage"

    // Класс (кеш) для для ускорения работы с файлами мессенджера без доступа к
    // файловой системе

    // alternative name is { t_path_holder, t_file_cacher, t_path_cacher }
    class t_meta_holder
        : public i_meta_holder
        , public i_rotator
    {
    public:
        t_meta_holder(const t_capacity minimum_capacity,
                      const t_capacity maximum_capacity,
                      t_meta_holder_cache&& paths);

        // implement i_meta_holder interface

        bool does_exist(const t_fs_path& path) const override;

        void do_register(const t_fs_path& path) override;

        // const time (O(1))
        void do_hold(const t_fs_path& path) override { do_register(path); }

        // void do_unhold(const t_fs_path& path) override { do_unregister(path); }

        void do_unregister(const t_fs_path& path) override;

        // implement i_rotator interface, todo: do we need to implement it here?

        void do_rotate(const t_fs& fs) override;

    protected:
        bool _does_exist(const t_fs_path& path) const;

        void _do_register(const t_fs_path& path);

        void _do_unregister(const t_fs_path& path);

        void _do_unregister_out_of_range(const t_fs& fs);

    protected:
        t_capacity_range _capacity_range;

        t_meta_holder_cache _cache;

        std::vector<t_fs_path> _to_remove;
    };
}

#endif // T_META_HOLDER_H
