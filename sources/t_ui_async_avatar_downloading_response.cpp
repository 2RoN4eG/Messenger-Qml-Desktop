#include "t_ui_async_avatar_downloading_response.h"

#include "t_image_storage_memory.h"
#include "t_image_info_storage_memory.h"
#include "t_path_maker.h"

#include <QMetaType>

namespace {
    t_qt_avatar make_avatar_by_thumb_hash(const t_image_info& info) {
        const t_thumb_hash thumb_hash = info._thumb_hash;
        if (thumb_hash.empty()) {
            return {};
        }
        return {};
    }
    
    t_qt_avatar make_squared_avatar(t_avatar_downloader_async_pointer& downloader) {
        t_qt_avatar avatar = downloader->get_avatar();
        downloader.reset();
        return avatar;
    }
}

//

Q_DECLARE_METATYPE(t_avatar_id);

t_ui_async_avatar_downloading_response::t_ui_async_avatar_downloading_response(const i_path_holder& path_holder,
                                                                               const i_image_info_storage& avatar_info_storage,
                                                                               i_image_storage& avatar_storage,
                                                                               const QSize& requested_size)
    : _path_holder { path_holder }
    , _avatar_info_storage { avatar_info_storage }
    , _avatar_storage { avatar_storage }
    , _size { requested_size }
    , _avatar { requested_size, t_qt_avatar::Format_Alpha8 }
{
    qRegisterMetaType<t_avatar_id>();

    _avatar.fill(Qt::transparent);
}

void t_ui_async_avatar_downloading_response::run(const t_avatar_id avatar_id) {
    const t_image_info& squared_info = _avatar_info_storage.get_image_info(avatar_id, _path_holder);

    if (_avatar_storage.does_image_exist_on_drive(squared_info)) {
        _avatar = _avatar_storage.read_image_from_drive(squared_info);
        emit_finished();
        return;
    }

    run_async_avatar_downloading(avatar_id, squared_info._url);

    if (does_avatar_info_contain_thumb_hash(squared_info)) {
        _avatar = make_avatar_by_thumb_hash(squared_info);
        emit_finished();
        return;
    }
}

QQuickTextureFactory* t_ui_async_avatar_downloading_response::textureFactory() const {
    return QQuickTextureFactory::textureFactoryForImage(
        _avatar.scaled(_size)
        );
}

void t_ui_async_avatar_downloading_response::emit_finished() {
    emit finished();
}

void t_ui_async_avatar_downloading_response::run_async_avatar_downloading(const t_avatar_id avatar_id, const t_url &url) {
    _downloading_command = std::make_unique<t_avatar_downloader_async>(avatar_id);
    connect(_downloading_command.get(), &t_avatar_downloader_async::downloaded, this, &t_ui_async_avatar_downloading_response::on_avatar_downloaded, Qt::QueuedConnection);
    _downloading_command->run(url);
}

void t_ui_async_avatar_downloading_response::on_avatar_downloaded(const t_avatar_id avatar_id) {
    _avatar = make_squared_avatar(_downloading_command);

    t_image_info&& squared_info = _avatar_info_storage.get_image_info(avatar_id, _path_holder);
    _avatar_storage.write_image_to_drive(_avatar, std::move(squared_info));

    emit_finished();
}
