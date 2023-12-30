#ifndef T_IMAGE_STORAGE_MEMORY_H
#define T_IMAGE_STORAGE_MEMORY_H

#include "t_defines.h"

#include <set>

#include <QUrl>

// forward declaration section

class i_qt_fs;
class i_meta_holder;
class i_avatar_path_aggregator;
class t_meta_holder_memory;
class t_image_info;

// interface section

class i_image_storage {
public:
    virtual bool does_image_exist_on_drive(const t_image_info& info) = 0;

    virtual t_qt_avatar read_image_from_drive(const t_image_info& info) = 0;

    virtual void write_image_to_drive(const t_qt_avatar& avatar, t_image_info&& info) = 0;
};

// declaration section

class t_image_storage_memory : public i_image_storage {
public:
    t_image_storage_memory(const i_qt_fs& fs, i_meta_holder& meta_holder);

    bool does_image_exist_on_drive(const t_image_info& info) override;

    t_qt_avatar read_image_from_drive(const t_image_info& info) override;

    void write_image_to_drive(const t_qt_avatar& avatar, t_image_info&& info) override;

private:
    const i_qt_fs& _fs;

    i_meta_holder& _meta_holder;
};

#endif // T_IMAGE_STORAGE_MEMORY_H
