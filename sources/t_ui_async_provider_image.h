#ifndef T_UI_ASYNC_PROVIDER_IMAGE_H
#define T_UI_ASYNC_PROVIDER_IMAGE_H

#include <QQuickImageResponse>

class i_image_info_storage;
class i_image_storage;
class i_path_holder;

class t_ui_async_provider_image : public QQuickAsyncImageProvider
{
public:
    t_ui_async_provider_image(const i_path_holder& path_holder,
                                 const i_image_info_storage& image_info_storage,
                                 i_image_storage& image_storage);

    QQuickImageResponse* requestImageResponse(const QString &id, const QSize &requestedSize) override;

private:
    const i_path_holder& _path_holder;

    const i_image_info_storage& _image_info_storage;

    i_image_storage& _image_storage;
};

#endif // T_UI_ASYNC_PROVIDER_IMAGE_H
