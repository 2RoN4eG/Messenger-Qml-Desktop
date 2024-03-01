#include "t_ui_async_image_response.h"

#include "memory/t_image_info_storage.h"

#include "t_image_fs_worker.h"
#include "t_path_aggregator.h"

#include <QMetaType>

#include <iostream>


namespace {
    t_qt_image make_avatar_by_thumb_hash(const t_thumb_hash& thumb_hash) {
        if (thumb_hash.empty()) {
            return {};
        }
        return {};
    }

    t_qt_image make_image(t_pointer_async_image_downloader& downloader) {
        t_qt_image image = downloader->get_image();
        downloader.reset();
        return image;
    }
}


Q_DECLARE_METATYPE(t_image_id);


t_ui_async_response_image::t_ui_async_response_image(i_image_worker& image_storage,
                                                     const i_path_maker& path_holder,
                                                     const i_image_info_storage& image_info_storage,
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

t_ui_async_response_image::~t_ui_async_response_image() {
}

void t_ui_async_response_image::run(const t_image_id image_id) {
    std::cout << "t_ui_async_response_image::run(const t_image_id image_id { " << image_id << " })" << std::endl;

    const t_fs_path& image_path = _image_info_storage.get_image_path(image_id, _path_holder);
    if (_image_storage.does_image_exist_on_drive(image_path)) {
        _image = _image_storage.read_image_from_drive(image_path);
        emit_finished();
        return;
    }

    const t_url& image_url = _image_info_storage.get_image_url(image_id);
    std::cout << "t_ui_async_response_image::run(...) url is '" << image_url.toString().toStdString() << "'" << std::endl;

    run_async_image_downloading(image_id, image_url);

    const t_thumb_hash& image_thumb_hash = _image_info_storage.get_image_thumb_hash(image_id);
    if (!image_thumb_hash.empty()) {
        _image = make_avatar_by_thumb_hash(image_thumb_hash);
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
    // std::cout << "t_ui_async_response_image::finished()" << std::endl;
    emit finished();
}

void t_ui_async_response_image::run_async_image_downloading(const t_image_id image_id, const t_url &url) {
    _downloading_command = std::make_unique<t_async_image_downloader>(image_id);
    connect(_downloading_command.get(), &t_async_image_downloader::downloaded, this, &t_ui_async_response_image::on_image_downloaded, Qt::QueuedConnection);
    _downloading_command->run(url);
}

void t_ui_async_response_image::on_image_downloaded(const t_image_id image_id) {
    _image = make_image(_downloading_command);

    const t_fs_path& image_path = _image_info_storage.get_image_path(image_id, _path_holder);
    _image_storage.write_image_to_drive(_image, image_path);

    emit_finished();
}
