#include "t_ui_async_avatar_creating_response.h"

#include "t_image_storage_memory.h"
#include "t_image_info_storage_memory.h"
#include "t_path_aggregator.h"

#include <QMetaType>

namespace {
    t_qt_avatar make_default_avatar(t_image_creator_async_pointer& creator) {
        t_qt_avatar avatar = creator->get_avatar();
        creator.reset();
        return avatar;
    }
}

Q_DECLARE_METATYPE(t_avatar_id);

//

t_ui_async_avatar_creating_response::t_ui_async_avatar_creating_response(const i_path_holder& path_holder,
                                                                         const i_image_info_storage& avatar_info_storage,
                                                                         i_image_storage& avatar_storage,
                                                                         const QSize& requested_size)
    : _path_holder { path_holder }
    , _avatar_info_storage { avatar_info_storage }
    , _avatar_storage { avatar_storage }
    , _size { requested_size }
{
    qRegisterMetaType<t_avatar_id>();
}

void t_ui_async_avatar_creating_response::run(const t_avatar_id avatar_id) {
    const t_image_info& default_info = _avatar_info_storage.get_image_info(avatar_id, _path_holder);

    const t_path& default_path = default_info._path;
    if (_avatar_storage.does_image_exist_on_drive(default_info)) {
        _avatar = _avatar_storage.read_image_from_drive(default_info);
        emit_finished();
        return;
    }

    run_async_avatar_creating(avatar_id, "?", _size);
}

QQuickTextureFactory* t_ui_async_avatar_creating_response::textureFactory() const {
    return QQuickTextureFactory::textureFactoryForImage(
        _avatar
        );
}

void t_ui_async_avatar_creating_response::emit_finished() {
    emit finished();
}

void t_ui_async_avatar_creating_response::run_async_avatar_creating(const t_avatar_id avatar_id, const t_qt_nickname nickname, const t_qt_size size) {
    _creating_command = std::make_unique<t_image_creator_async>(avatar_id);
    connect(_creating_command.get(), &t_image_creator_async::created, this, &t_ui_async_avatar_creating_response::on_avatar_created, Qt::QueuedConnection);
    _creating_command->run("?", size);
}

void t_ui_async_avatar_creating_response::on_avatar_created(const t_avatar_id avatar_id) {
    _avatar = make_default_avatar(_creating_command);

    t_image_info&& default_info = _avatar_info_storage.get_image_info(avatar_id, _path_holder);
    _avatar_storage.write_image_to_drive(_avatar, std::move(default_info));

    emit_finished();
}
