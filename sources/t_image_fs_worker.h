#ifndef T_IMAGE_FS_WORKER_H
#define T_IMAGE_FS_WORKER_H

#include "t_defines.h"

#include <QUrl>


// forward declaration section

class i_qt_fs;
class i_meta_holder;
class i_avatar_path;
class t_memory_meta_holder;
class t_image_info;


// interface section

class i_image_worker
{
public:
    virtual bool does_image_exist_on_drive(const t_fs_path& path) = 0;

    virtual t_qt_avatar read_image_from_drive(const t_fs_path& path) = 0;

    virtual void write_image_to_drive(const t_qt_avatar& avatar, const t_fs_path& path) = 0;
};


// class (interface's implementation) section

class t_image_fs_worker : public i_image_worker
{
public:
    t_image_fs_worker(const i_qt_fs& fs, i_meta_holder& meta_holder);

    bool does_image_exist_on_drive(const t_fs_path& path) override;

    t_qt_avatar read_image_from_drive(const t_fs_path& path) override;

    void write_image_to_drive(const t_qt_avatar& avatar, const t_fs_path& path) override;

private:
    const i_qt_fs& _fs;

    i_meta_holder& _meta_holder;
};

#endif // T_IMAGE_FS_WORKER_H
