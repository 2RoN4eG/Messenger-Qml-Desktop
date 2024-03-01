#include "t_ui_async_default_avatar_response.h"

#include "t_image_fs_worker.h"
#include "t_path_aggregator.h"

#include "memory/t_image_info_storage.h"

#include <QMetaType>

namespace {
t_qt_image make_default_image(t_image_creator_async_pointer& creator) {
    t_qt_image image = creator->get_image();
    creator.reset();
    return image;
}
}

Q_DECLARE_METATYPE(t_image_id);

//

t_ui_async_response_default_avatar::t_ui_async_response_default_avatar(const i_path_maker& path_holder,
                                                                       const i_image_info_storage& image_info_storage,
                                                                       const t_qt_size& size,
                                                                       i_image_worker& image_storage)
    : _path_holder { path_holder }
    , _image_info_storage { image_info_storage }
    , _size { size }
    , _image_storage { image_storage }
{
    qRegisterMetaType<t_image_id>();
}

void t_ui_async_response_default_avatar::run(const t_image_id image_id) {
    const t_fs_path& default_image_path = _image_info_storage.get_image_path(image_id, _path_holder);
    if (_image_storage.does_image_exist_on_drive(default_image_path)) {
        _image = _image_storage.read_image_from_drive(default_image_path);
        emit_finished();
        return;
    }

    run_async_image_creating(image_id, "?", _size);
}

QQuickTextureFactory* t_ui_async_response_default_avatar::textureFactory() const {
    return QQuickTextureFactory::textureFactoryForImage(_image);
}

void t_ui_async_response_default_avatar::emit_finished() {
    emit finished();
}

void t_ui_async_response_default_avatar::run_async_image_creating(const t_image_id image_id, const t_qt_nickname nickname, const t_qt_size& size) {
    _creating_command = std::make_unique<t_async_default_avatar_creator>(image_id);
    connect(_creating_command.get(), &t_async_default_avatar_creator::created, this, &t_ui_async_response_default_avatar::on_image_created, Qt::QueuedConnection);
    _creating_command->run("?", size);
}

void t_ui_async_response_default_avatar::on_image_created(const t_image_id image_id) {
    _image = make_default_image(_creating_command);

    const t_fs_path& default_image_path = _image_info_storage.get_image_path(image_id, _path_holder);
    _image_storage.write_image_to_drive(_image, default_image_path);

    emit_finished();
}
