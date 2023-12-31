#include "t_meta_holder_memory.h"

#include "t_fs.h"

#include <iostream>

struct t_sorter_by_timestamp {
    constexpr bool operator()(const t_fs_meta& lhs, const t_fs_meta& rhs) const {
        return lhs._timestamp > rhs._timestamp;
    }
};

using t_sorted_by_timestamp_paths = std::multiset<t_fs_meta>;

t_sorted_by_timestamp_paths make_sorted_by_timestamp(const std::set<t_fs_path>& paths, const t_fs& fs) {
    t_sorted_by_timestamp_paths sorted;

    for (const t_fs_path& path : paths) {
        if (is_directory(path)) {
            continue;
        }

        auto size = fs.get_size(path);
        auto timestamp = fs.get_timestamp(path);

        sorted.emplace(path, size, timestamp);
    }

    return sorted;
}

t_sorted_by_timestamp_paths::iterator get_out_of_capacity_iterator(
    const t_sorted_by_timestamp_paths& sorted, const size_t capacity,
    const t_sorted_by_timestamp_paths::iterator since, size_t& cached_size) {
    if (since == sorted.end()) {
        return sorted.end();
    }

    for (auto it = since; it != sorted.end(); ++it) {
        if (cached_size += it->_size; cached_size > capacity) {
            return it;
        }
    }

    return sorted.end();
}

//

t_meta_holder_memory::t_meta_holder_memory(t_fs_size minimum_capacity, t_fs_size maximum_capacity, t_cache&& cache)
    : _minimum_capacity { minimum_capacity }
    , _maximum_capacity { maximum_capacity }
    , _cache { std::move(cache) }
{
    for (const t_fs_path& path : _cache) {
        std::cout << "t_memory_meta_holder path is " << path << std::endl;
    }
}

bool t_meta_holder_memory::does_exist(const t_fs_path& path) const {
    return _does_exist(path);
}

// const time (O(1))
void t_meta_holder_memory::do_register(const t_fs_path& path) {
    _do_register(path);
}

// const time (O(1))
void t_meta_holder_memory::do_unregister(const t_fs_path& path) {
    _do_unregister(path);
}

// Complexity does not matter (will be run separately in different thread)
void t_meta_holder_memory::do_rotate(const t_fs& fs) {
    _do_unregister_out_of_capacity(fs);
    std::vector<t_fs_path> to_remove = std::exchange(_to_remove, {});
    for (const t_fs_path& path : to_remove) {
        fs.do_remove(path);
    }
}

bool t_meta_holder_memory::_does_exist(const t_fs_path &path) const {
    return std::ranges::find(_cache, path) != _cache.end();
}

void t_meta_holder_memory::_do_register(const t_fs_path &path) {
    _cache.emplace(path);
}

// const time (O(1))
void t_meta_holder_memory::_do_unregister(const t_fs_path& path) {
    if (auto it = std::find(_cache.cbegin(), _cache.cend(), path); it != _cache.end()) {
        _cache.erase(it);
    }
    _to_remove.emplace_back(path);
}

// Complexity is O(N)
void t_meta_holder_memory::_do_unregister_out_of_capacity(const t_fs& fs) {
    const auto sorted = make_sorted_by_timestamp(_cache, fs);
    
    t_fs_size cached_size {};

    const auto since = get_out_of_capacity_iterator(sorted, _minimum_capacity, sorted.begin(), cached_size);
    if (since == sorted.end()) {
        return;
    }

    const bool need_unregister = (get_out_of_capacity_iterator(sorted, _maximum_capacity, since, cached_size) != sorted.end());
    if (!need_unregister) {
        return;
    }

    for (auto it = since; it != sorted.end(); ++it) {
        _do_unregister(it->_path);
    }
}
