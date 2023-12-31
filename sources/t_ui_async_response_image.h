#ifndef T_UI_ASYNC_RESPONSE_IMAGE_H
#define T_UI_ASYNC_RESPONSE_IMAGE_H

#include "t_defines.h"

#include "t_async_image_downloader.h"

#include <QQuickAsyncImageProvider>
#include <QNetworkAccessManager>

class i_image_storage;
class i_image_info_storage;
class i_path_holder;

class QQuickTextureFactory;

class t_ui_async_response_image : public QQuickImageResponse
{
public:
    t_ui_async_response_image(const i_path_holder& path_holder,
                                           const i_image_info_storage& image_info_storage,
                                           i_image_storage& image_storage,
                                           const QSize& size);

    void run(const t_image_id image_id);

    QQuickTextureFactory *textureFactory() const override;

protected:
    void emit_finished();

    void run_async_image_downloading(const t_image_id image_id, const t_url& url);

protected slots:
    void on_image_downloaded(const t_image_id image_id);

protected:
    t_pointer_async_image_downloader _downloading_command;

private:
    const i_path_holder& _path_holder;

    const i_image_info_storage& _image_info_storage;
    
    i_image_storage& _image_storage;

    QSize _size;

    t_qt_image _image;

    QNetworkAccessManager _network;
};

#endif // T_UI_ASYNC_RESPONSE_IMAGE_H
