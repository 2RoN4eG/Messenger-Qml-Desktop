#include "t_image_fs_worker.h"

#include "memory/t_memory_meta_holder.h"
#include "t_image_info.h"
#include "t_fs.h"

//

t_image_fs_worker::t_image_fs_worker(const i_qt_fs& fs, i_meta_holder& meta_holder)
    : _fs { fs }
    , _meta_holder { meta_holder }
{
}

bool t_image_fs_worker::does_image_exist_on_drive(const t_image_info& info) {
    const t_fs_path& path = info._path;
    if (path.empty()) {
        throw std::runtime_error { "avatar path to check existing on drive is empty" };
    }

    if (!_meta_holder.does_exist(path)) {
        return false;
    }

    return _fs.does_exist(path);
}

t_qt_avatar t_image_fs_worker::read_image_from_drive(const t_image_info& info) {
    const t_fs_path& path = info._path;
    if (path.empty()) {
        throw std::runtime_error { "avatar path to read from drive is empty" };
    }

    if (!_meta_holder.does_exist(path)) {
        throw std::runtime_error { "avatar path does not exist in meta holder" };
    }

    return _fs.do_read_from_drive(path);
}

void t_image_fs_worker::write_image_to_drive(const t_qt_avatar& avatar, t_image_info&& info) {
    const t_fs_path& path = info._path;
    if (path.empty()) {
        throw std::runtime_error { "avatar path to write on drive is empty" };
    }

    _fs.do_write_to_drive(avatar, path);

    _meta_holder.do_register(path);
}
