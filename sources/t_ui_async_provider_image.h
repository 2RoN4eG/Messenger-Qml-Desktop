#ifndef T_UI_ASYNC_PROVIDER_IMAGE_H
#define T_UI_ASYNC_PROVIDER_IMAGE_H

#include <QQuickImageResponse>

class i_image_info_storage;
class i_image_worker;
class i_make_path;

class t_ui_async_provider_image : public QQuickAsyncImageProvider
{
public:
    t_ui_async_provider_image(const i_make_path& path_holder,
                                 const i_image_info_storage& image_info_storage,
                              i_image_worker& image_storage);

    QQuickImageResponse* requestImageResponse(const QString &id, const QSize &requestedSize) override;

private:
    const i_make_path& _path_holder;

    const i_image_info_storage& _image_info_storage;
    
    i_image_worker& _image_storage;
};

#endif // T_UI_ASYNC_PROVIDER_IMAGE_H
