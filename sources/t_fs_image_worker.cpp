#include "t_fs_image_worker.h"

#include "interfaces/i_meta_holder.h"
#include "t_fs.h"


t_fs_image_worker::t_fs_image_worker(const i_fs_qt& fs, i_meta_holder& meta_holder)
    : _fs { fs }
    , _meta_holder { meta_holder }
{
}

bool t_fs_image_worker::does_image_exist_on_drive(const t_fs_path& path) const
{
    if (path.empty())
    {
        throw std::runtime_error { "image path to check existing on drive is empty" };
    }

    if (!_meta_holder.does_exist(path))
    {
        return false;
    }

    return _fs.does_exist(path);
}

t_ui_image t_fs_image_worker::read_image_from_drive(const t_fs_path& path) const
{
    if (path.empty())
    {
        throw std::runtime_error { "image path to read from drive is empty" };
    }

    if (!_meta_holder.does_exist(path))
    {
        throw std::runtime_error { "image path does not exist in meta holder, call does_image_exist_on_drive to check existing before" };
    }

    return _fs.do_read_from_drive(path);
}

void t_fs_image_worker::write_image_to_drive(const t_fs_path& path, const t_ui_image& image)
{
    if (path.empty())
    {
        throw std::runtime_error { "path to writing image to drive is empty" };
    }

    _fs.do_write_to_drive(path, image);

    _meta_holder.do_register(path);
}
