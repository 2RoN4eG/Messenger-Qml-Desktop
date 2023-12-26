#include "t_qt_default_avatar_response.h"

#include "../t_fs_image_worker.h"
#include "../t_path_aggregator.h"

#include "../memory/t_storage_image_info.h"

#include <QMetaType>
#include <iostream>

namespace
{
    t_ui_image make_default_image(async::t_qt_default_avatar_creator_pointer& creator)
    {
        t_ui_image image = creator->get_image();

        creator.reset();

        return image;
    }
}

Q_DECLARE_METATYPE(t_image_id);

//

t_qt_default_avatar_response::t_qt_default_avatar_response(const i_image_fs_path_maker& path_holder,
                                                     const i_image_info_storage& image_info_storage,
                                                     const t_ui_size& size,
                                                     i_fs_image_worker& image_storage)
    : _path_holder { path_holder }
    , _image_info_storage { image_info_storage }
    , _size { size }
    , _image_storage { image_storage }
{
    qRegisterMetaType<t_image_id>();
}

void t_qt_default_avatar_response::run(const t_image_id image_id)
{
    const t_fs_path& default_image_path = _image_info_storage.get_image_fs_path(image_id, _path_holder);

    if (_image_storage.does_image_exist_on_drive(default_image_path))
    {
        _image = _image_storage.read_image_from_drive(default_image_path);

        emit_finished();

        return;
    }

    run_async_image_creating(image_id, "?", _size);
}

QQuickTextureFactory* t_qt_default_avatar_response::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(_image);
}

void t_qt_default_avatar_response::emit_finished()
{
    emit finished();
}

void t_qt_default_avatar_response::run_async_image_creating(const t_image_id image_id, const t_ui_nickname nickname, const t_ui_size& size)
{
    _command = async::make_qt_async_default_avatar_creator_pointer();

    connect(_command.get(), &async::t_qt_async_default_avatar_creator::created, this, &t_qt_default_avatar_response::on_image_created, Qt::QueuedConnection);

    _command->run(image_id, "?", size);
}

void t_qt_default_avatar_response::on_image_created(const t_image_id image_id)
{
    _image = make_default_image(_command);
    
    t_fs_path default_image_path = _image_info_storage.get_image_fs_path(image_id, _path_holder);

    _image_storage.write_image_to_drive(_image, std::move(default_image_path));

    emit_finished();
}
