#include "t_qt_image_response.h"

#include "../interfaces/i_fs_image_worker.h"
#include "../memory/t_storage_image_info.h"
#include "../t_path_aggregator.h"

#include <QMetaType>

namespace
{
    t_ui_image make_avatar_by_thumb_hash(const t_thumb_hash& thumb_hash)
    {
        if (thumb_hash.empty())
        {
            return {};
        }
        return {};
    }

    t_ui_image get_image(async::t_qt_async_image_downloader_pointer& downloader) {
        const t_ui_image image = downloader->get_image();
        downloader.reset();
        return image;
    }
}


Q_DECLARE_METATYPE(t_image_id);


t_qt_image_response::t_qt_image_response(i_fs_image_worker& image_storage,
                                         const i_image_fs_path_maker& path_maker,
                                         const i_image_info_storage& image_info_storage,
                                         const QSize& size)
    : _path_maker { path_maker }
    , _image_info_storage { image_info_storage }
    , _image_storage { image_storage }
    , _size { size }
    , _image { size, t_ui_image::Format_Alpha8 }
{
    qRegisterMetaType<t_image_id>();

    _image.fill(Qt::transparent);
}

void t_qt_image_response::run(const t_image_id image_id)
{
    const t_fs_path& image_path = _image_info_storage.get_image_fs_path(image_id, _path_maker);
    if (_image_storage.does_image_exist_on_drive(image_path))
    {
        _image = _image_storage.read_image_from_drive(image_path);
        emit_finished();

        return;
    }

    const t_url& image_url = _image_info_storage.get_image_url(image_id);
    run_async_image_downloading(image_id, image_url);

    const t_thumb_hash& image_thumb_hash = _image_info_storage.get_image_thumb_hash(image_id);
    if (!image_thumb_hash.empty())
    {
        _image = make_avatar_by_thumb_hash(image_thumb_hash);
        emit_finished();

        return;
    }
}

QQuickTextureFactory* t_qt_image_response::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(_image.scaled(_size));
}

void t_qt_image_response::emit_finished()
{
    emit finished();
}

void t_qt_image_response::run_async_image_downloading(const t_image_id image_id, const t_url& url)
{
    _command = async::make_qt_async_image_downloader();

    connect(_command.get(),
            &async::t_qt_async_image_downloader::downloaded,
            this,
            &t_qt_image_response::on_image_downloaded,
            Qt::QueuedConnection);

    _command->run(image_id, url);
}

void t_qt_image_response::on_image_downloaded(const t_image_id image_id)
{
    _image = get_image(_command);

    t_fs_path image_path = _image_info_storage.get_image_fs_path(image_id, _path_maker);

    _image_storage.write_image_to_drive(_image, std::move(image_path));

    emit_finished();
}
