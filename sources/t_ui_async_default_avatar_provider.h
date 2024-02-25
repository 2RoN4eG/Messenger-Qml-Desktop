#ifndef T_UI_ASYNC_DEFAULT_AVATAR_PROVIDER_H
#define T_UI_ASYNC_DEFAULT_AVATAR_PROVIDER_H

#include <QQuickImageResponse>

class i_image_info_storage;
class i_image_worker;
class i_path_maker;

class t_ui_async_provider_default_avatar : public QQuickAsyncImageProvider
{
public:
    t_ui_async_provider_default_avatar(const i_path_maker& path_holder,
                                 const i_image_info_storage& avatar_info_storage,
                                       i_image_worker& avatar_storage);

    QQuickImageResponse* requestImageResponse(const QString& id, const QSize& size) override;

private:
    const i_path_maker& _path_holder;

    const i_image_info_storage& _image_info_storage;
    
    i_image_worker& _image_storage;
};

#endif // T_UI_ASYNC_DEFAULT_AVATAR_PROVIDER_H
