#ifndef T_QT_IMAGE_RESPONSE_H
#define T_QT_IMAGE_RESPONSE_H

#include "../t_defines.h"

#include "../async/t_qt_async_image_downloader.h"

#include <QQuickAsyncImageProvider>
#include <QNetworkAccessManager>

class i_fs_image_worker;
class i_image_component_storage;
class i_file_fs_path_maker;

class QQuickTextureFactory;

class t_qt_image_response
    : public QQuickImageResponse
{
public:
    t_qt_image_response(i_fs_image_worker& image_storage,
                        const i_file_fs_path_maker& path_maker,
                        const i_image_component_storage& image_component_storage,
                        const QSize& size);
    ~t_qt_image_response() override = default;

    void run(const t_image_id image_id);

    QQuickTextureFactory* textureFactory() const override;

protected:
    void emit_finished();

    void run_async_image_downloading(const t_image_id image_id, const t_url& url);

protected slots:
    void on_image_downloaded(const t_image_id image_id);

protected:
    async::t_qt_async_image_downloader_pointer _command;

private:
    i_fs_image_worker& _image_storage;
    
    t_ui_image _image;

    QNetworkAccessManager _network;
    
    const i_file_fs_path_maker& _path_maker;

    const i_image_component_storage& _image_component_storage;

    const QSize _size;
};

#endif // T_QT_IMAGE_RESPONSE_H
