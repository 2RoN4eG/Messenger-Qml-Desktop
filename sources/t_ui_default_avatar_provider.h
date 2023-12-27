#ifndef T_UI_DEFAULT_AVATAR_PROVIDER_H
#define T_UI_DEFAULT_AVATAR_PROVIDER_H

#include <QQuickImageResponse>

class i_image_info_storage;
class i_image_storage;
class i_path_holder;

class t_ui_default_avatar_provider : public QQuickAsyncImageProvider
{
public:
    t_ui_default_avatar_provider(const i_path_holder& path_holder,
                                 const i_image_info_storage& avatar_info_storage,
                                 i_image_storage& avatar_storage);

    QQuickImageResponse* requestImageResponse(const QString &id, const QSize &requested_size) override;

private:
    const i_path_holder& _path_holder;

    const i_image_info_storage& _image_info_storage;

    i_image_storage& _image_storage;
};

#endif // T_UI_DEFAULT_AVATAR_PROVIDER_H
