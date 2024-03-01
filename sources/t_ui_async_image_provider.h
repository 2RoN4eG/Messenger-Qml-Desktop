#ifndef T_UI_ASYNC_IMAGE_PROVIDER_H
#define T_UI_ASYNC_IMAGE_PROVIDER_H

#include "t_defines.h"

#include <QQuickImageResponse>


class i_image_info_storage;
class i_image_worker;
class i_path_maker;


class t_ui_async_image_provider : public QQuickAsyncImageProvider
{
public:
    t_ui_async_image_provider(const i_path_maker& path_holder,
                              const i_image_info_storage& image_info_storage,
                              i_image_worker& image_storage);

    QQuickImageResponse* requestImageResponse(const QString &id, const t_qt_size& size) override;

private:
    const i_path_maker& _path_holder;

    const i_image_info_storage& _image_info_storage;
    
    i_image_worker& _image_storage;
};

#endif // T_UI_ASYNC_IMAGE_PROVIDER_H
