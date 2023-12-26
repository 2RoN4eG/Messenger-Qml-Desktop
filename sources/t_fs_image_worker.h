#ifndef T_FS_IMAGE_WORKER_H
#define T_FS_IMAGE_WORKER_H

#include "interfaces/i_fs_image_worker.h"

// forward declaration section

class i_fs_qt;
class i_meta_holder;
class i_avatar_fs_path;
class t_memory_meta_holder;
class t_image_info;

// interface section


// class (interface's implementation) section

// Уровень работы с картинками до обращения в файловую систему и сохранение путей для удаления и проверки выхода за размер

class t_fs_image_worker : public i_fs_image_worker
{
public:
    t_fs_image_worker(const i_fs_qt& fs, i_meta_holder& meta_holder);
    ~t_fs_image_worker() = default;

    bool does_image_exist_on_drive(const t_fs_path& path) override;

    t_ui_image read_image_from_drive(const t_fs_path& path) override;

    void write_image_to_drive(const t_ui_image& image, t_fs_path&& path) override;

private:
    const i_fs_qt& _fs;

    i_meta_holder& _meta_holder;
};

#endif // T_FS_IMAGE_WORKER_H
