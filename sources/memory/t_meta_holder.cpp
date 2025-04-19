#include "t_meta_holder.hpp"

#include "../t_fs.h"
#include "../t_defines.h"

#include <iostream>


namespace
{
    struct t_sorter_by_timestamp
    {
        constexpr bool operator()(const t_fs_meta& lhs, const t_fs_meta& rhs) const
        {
            return lhs._timestamp > rhs._timestamp;
        }
    };

    using t_sorted_by_timestamp_paths = std::multiset<t_fs_meta>;

    using t_paths_iterator = t_sorted_by_timestamp_paths::iterator;

    t_sorted_by_timestamp_paths make_sorted_by_timestamp(const std::set<t_fs_path>& paths, const t_fs& fs)
    {
        t_sorted_by_timestamp_paths sorted;

        for (const t_fs_path& path : paths)
        {
            if (is_directory(path))
            {
                continue;
            }

            t_fs_size size           = fs.get_size(path);
            t_fs_timestamp timestamp = fs.get_timestamp(path);

            sorted.emplace(path, size, timestamp);
        }

        return sorted;
    }

    t_paths_iterator get_out_of_capacity_iterator(const t_sorted_by_timestamp_paths& sorted, const t_paths_iterator since, const size_t capacity, size_t& cached_size)
    {
        if (since == sorted.end())
        {
            return sorted.end();
        }

        for (t_sorted_by_timestamp_paths::iterator iterator = since; iterator != sorted.end(); ++iterator)
        {
            cached_size += iterator->_size;

            if (cached_size > capacity)
            {
                return iterator;
            }
        }

        return sorted.end();
    }
}


namespace memory
{
    t_meta_holder::t_meta_holder(t_fs_size minimum_capacity, t_fs_size maximum_capacity, t_meta_holder_cache&& cache)
        : _capacity_range { minimum_capacity, maximum_capacity }
        , _cache { std::move(cache) }
    {
        std::cout << "range is " << minimum_capacity << " ... " << maximum_capacity << std::endl;

        for (const t_fs_path& path : _cache)
        {
            std::cout << "t_memory_meta_holder path is " << path << std::endl;
        }
    }

    bool t_meta_holder::does_exist(const t_fs_path& path) const
    {
        return _does_exist(path);
    }

    // const time (O(1))
    void t_meta_holder::do_register(const t_fs_path& path)
    {
        _do_register(path);
    }

    // const time (O(1))
    void t_meta_holder::do_unregister(const t_fs_path& path)
    {
        _do_unregister(path);
    }

    // Complexity does not matter (will be run separately in different thread)
    void t_meta_holder::do_rotate(const t_fs& fs)
    {
        _do_unregister_out_of_range(fs);

        std::vector<t_fs_path> to_remove = std::exchange(_to_remove, {});

        for (const t_fs_path& path : to_remove)
        {
            fs.do_directories_remove(path);
        }
    }

    bool t_meta_holder::_does_exist(const t_fs_path &path) const
    {
        return std::ranges::find(_cache, path) != _cache.end();
    }

    void t_meta_holder::_do_register(const t_fs_path &path)
    {
        _cache.emplace(path);
    }

    // const time (O(1))
    void t_meta_holder::_do_unregister(const t_fs_path& path)
    {
        if (t_meta_holder_cache::iterator iterator = std::find(_cache.cbegin(), _cache.cend(), path); iterator != _cache.end())
        {
            _cache.erase(iterator);
        }

        _to_remove.emplace_back(path);
    }

    // Complexity is O(N)
    void t_meta_holder::_do_unregister_out_of_range(const t_fs& fs)
    {
        const t_sorted_by_timestamp_paths sorted = make_sorted_by_timestamp(_cache, fs);

        t_fs_size cached_size {};
        const t_sorted_by_timestamp_paths::iterator since = get_out_of_capacity_iterator(sorted, sorted.begin(), _capacity_range._minimum, cached_size);

        if (since == sorted.end())
        {
            return;
        }

        if (get_out_of_capacity_iterator(sorted, since, _capacity_range._maximum, cached_size) == sorted.end())
        {
            return;
        }

        for (t_sorted_by_timestamp_paths::iterator iterator = since; iterator != sorted.end(); ++iterator)
        {
            _do_unregister(iterator->_path);
        }
    }
}
