#ifndef T_FS_H
#define T_FS_H

#include "t_defines.h"

#include <set>

class i_fs {
    // works with filesystem using std::filesystem
public:
    virtual bool does_exist(const t_fs_path& path) const = 0;

    virtual bool is_directory(const t_fs_path& path) const = 0;

    virtual void do_create_directories(const t_fs_path& path) const = 0;

    virtual std::set<t_fs_path> get_paths_in_directory(const t_fs_path& path) const = 0;

    virtual std::set<t_fs_meta> get_metas_in_directory(const t_fs_path& path) const = 0;

    virtual void do_remove(const t_fs_path& path) const = 0;
    
    virtual t_fs_size get_size(const t_fs_path& path) const = 0;
    
    virtual t_fs_timestamp get_timestamp(const t_fs_path& path) const = 0;

    virtual t_fs_line read_as_single_line(const t_fs_path& path) const = 0;
};

class i_qt_fs {
    // works with images using Qt
public:
    virtual bool does_exist(const t_fs_path& path) const = 0;

    virtual void do_write_to_drive(const t_qt_image& image, const t_fs_path& path) const = 0;

    virtual t_qt_image do_read_from_drive(const t_fs_path& path) const = 0;
};

class t_fs : public i_fs, public i_qt_fs
{
public:
    // imlementation of i_fs & i_qt_fs

    bool does_exist(const t_fs_path& path) const override;

    // imlementation of i_fs

    bool is_directory(const t_fs_path& path) const override;

    void do_create_directories(const t_fs_path& path) const override;

    std::set<t_fs_path> get_paths_in_directory(const t_fs_path& path) const override;

    std::set<t_fs_meta> get_metas_in_directory(const t_fs_path& path) const override;

    void do_remove(const t_fs_path& path) const override;
    
    t_fs_size get_size(const t_fs_path& path) const override;
    
    t_fs_timestamp get_timestamp(const t_fs_path& path) const override;

    t_fs_line read_as_single_line(const t_fs_path& path) const override;

    // implementation of i_qt_fs

    void do_write_to_drive(const t_qt_image& image, const t_fs_path& path) const override;

    t_qt_image do_read_from_drive(const t_fs_path& path) const override;
};

#endif // T_FS_H
