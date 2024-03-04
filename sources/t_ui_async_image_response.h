#ifndef T_UI_ASYNC_IMAGE_RESPONSE_H
#define T_UI_ASYNC_IMAGE_RESPONSE_H

#include "t_defines.h"

#include "t_async_image_downloader.h"

#include <QQuickAsyncImageProvider>
#include <QNetworkAccessManager>

class i_image_worker;
class i_image_info_storage;
class i_path_maker;

class QQuickTextureFactory;

class t_ui_async_response_image : public QQuickImageResponse
{
public:
    t_ui_async_response_image(i_image_worker& image_storage,
                              const i_path_maker& path_holder,
                              const i_image_info_storage& image_info_storage,
                              const QSize& size);
    ~t_ui_async_response_image();

    void run(const t_image_id image_id);

    QQuickTextureFactory *textureFactory() const override;

protected:
    void emit_finished();

    void run_async_image_downloading(const t_image_id image_id, const t_url& url);

protected slots:
    void on_image_downloaded(const t_image_id image_id);

protected:
    t_async_image_downloader_pointer _downloading_command;

private:
    const i_path_maker& _path_holder;

    const i_image_info_storage& _image_info_storage;

    i_image_worker& _image_storage;

    QSize _size;

    t_qt_image _image;

    QNetworkAccessManager _network;
};

#endif // T_UI_ASYNC_IMAGE_RESPONSE_H
