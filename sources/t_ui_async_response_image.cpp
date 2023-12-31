#include "t_ui_async_response_image.h"

#include "t_image_storage_memory.h"
#include "t_image_info_storage_memory.h"
#include "t_path_aggregator.h"

namespace {
    t_qt_image make_avatar_by_thumb_hash(const t_image_info& info) {
        const t_thumb_hash thumb_hash = info._thumb_hash;
        if (thumb_hash.empty()) {
            return {};
        }
        return {};
    }

    t_qt_image make_squared_image(t_pointer_async_image_downloader& downloader) {
        t_qt_image image = downloader->get_image();
        downloader.reset();
        return image;
    }
}

//

t_ui_async_response_image::t_ui_async_response_image(const i_path_holder& path_holder,
                                                                               const i_image_info_storage& image_info_storage,
                                                                               i_image_storage& image_storage,
                                                                               const QSize& size)
    : _path_holder { path_holder }
    , _image_info_storage { image_info_storage }
    , _image_storage { image_storage }
    , _size { size }
    , _image { size, t_qt_image::Format_Alpha8 }
{
    qRegisterMetaType<t_image_id>();

    _image.fill(Qt::transparent);
}

void t_ui_async_response_image::run(const t_image_id image_id) {
    const t_image_info& squared_info = _image_info_storage.get_image_info(image_id, _path_holder);

    if (_image_storage.does_image_exist_on_drive(squared_info)) {
        _image = _image_storage.read_image_from_drive(squared_info);
        emit_finished();
        return;
    }

    run_async_image_downloading(image_id, squared_info._url);

    if (does_avatar_info_contain_thumb_hash(squared_info)) {
        _image = make_avatar_by_thumb_hash(squared_info);
        emit_finished();
        return;
    }
}

QQuickTextureFactory* t_ui_async_response_image::textureFactory() const {
    return QQuickTextureFactory::textureFactoryForImage(
        _image.scaled(_size)
        );
}

void t_ui_async_response_image::emit_finished() {
    emit finished();
}

void t_ui_async_response_image::run_async_image_downloading(const t_image_id image_id, const t_url &url) {
    _downloading_command = std::make_unique<t_async_image_downloader>(image_id);
    connect(_downloading_command.get(), &t_async_image_downloader::downloaded, this, &t_ui_async_response_image::on_image_downloaded, Qt::QueuedConnection);
    _downloading_command->run(url);
}

void t_ui_async_response_image::on_image_downloaded(const t_image_id image_id) {
    _image = make_squared_image(_downloading_command);

    t_image_info&& squared_info = _image_info_storage.get_image_info(image_id, _path_holder);
    _image_storage.write_image_to_drive(_image, std::move(squared_info));

    emit_finished();
}
