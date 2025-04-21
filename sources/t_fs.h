#ifndef T_FS_H
#define T_FS_H

#include "t_defines.h"

#include <set>


class i_fs_common
{
public:
    virtual bool does_path_exist(const t_fs_path& path) const = 0;
};


// works with filesystem using std::filesystem
class i_fs_std : public i_fs_common
{
public:
    virtual bool is_directory(const t_fs_path& path) const = 0;

    virtual void create_directories(const t_fs_path& path) const = 0;

    virtual std::set<t_fs_path> get_directory_file_paths(const t_fs_path& path) const = 0;

    virtual t_fs_metas get_metas_in_directory(const t_fs_path& path) const = 0;

    virtual void do_directories_remove(const t_fs_path& path) const = 0;

    virtual t_fs_size get_size(const t_fs_path& path) const = 0;

    virtual t_fs_timestamp get_timestamp(const t_fs_path& path) const = 0;

    virtual t_fs_line read_as_single_line(const t_fs_path& path) const = 0;
};


// works with images using Qt
class i_fs_qt : public i_fs_common
{
public:
    virtual void do_write_image_to_drive(const t_fs_path& path, const t_ui_image& image) const = 0;

    virtual t_ui_image do_read_image_from_drive(const t_fs_path& path) const = 0;
};


class t_fs : public i_fs_std, public i_fs_qt
{
public:
    // imlementation of i_fs_common

    bool does_path_exist(const t_fs_path& path) const override;

    // imlementation of i_fs

    bool is_directory(const t_fs_path& path) const override;
    
    void create_directories(const t_fs_path& path) const override;

    std::set<t_fs_path> get_directory_file_paths(const t_fs_path& path) const override;

    t_fs_metas get_metas_in_directory(const t_fs_path& path) const override;

    void do_directories_remove(const t_fs_path& path) const override;
    
    t_fs_size get_size(const t_fs_path& path) const override;
    
    t_fs_timestamp get_timestamp(const t_fs_path& path) const override;

    t_fs_line read_as_single_line(const t_fs_path& path) const override;

    // implementation of i_qt_fs

    void do_write_image_to_drive(const t_fs_path& path, const t_ui_image& image) const override;

    t_ui_image do_read_image_from_drive(const t_fs_path& path) const override;
};


inline t_fs_line t_read_file_as_single_line(const t_fs_path& path)
{
    return t_fs {}.read_as_single_line(path);
}

#endif // T_FS_H
