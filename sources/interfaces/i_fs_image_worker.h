#ifndef I_FS_IMAGE_WORKER_H
#define I_FS_IMAGE_WORKER_H

#include "../t_defines.h"

class i_fs_image_worker
{
public:
    virtual ~i_fs_image_worker() = 0;

    virtual bool does_image_exist_on_drive(const t_fs_path& path) const = 0;

    virtual t_ui_image read_image_from_drive(const t_fs_path& path) const = 0;

    virtual void write_image_to_drive(const t_ui_image& image, t_fs_path&& path) = 0;
};

#endif // I_FS_IMAGE_WORKER_H
