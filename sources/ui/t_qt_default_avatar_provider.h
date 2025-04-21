#ifndef T_QT_DEFAULT_AVATAR_PROVIDER_H
#define T_QT_DEFAULT_AVATAR_PROVIDER_H

#include <QQuickAsyncImageProvider>

class i_image_component_storage;
class i_fs_image_worker;
class i_file_fs_path_maker;

class QQuickImageResponse;

class t_qt_default_avatar_provider
    : public QQuickAsyncImageProvider
{
public:
    t_qt_default_avatar_provider(const i_file_fs_path_maker& path_maker,
                                 const i_image_component_storage& avatar_component_storage,
                                 i_fs_image_worker& avatar_storage);
    ~t_qt_default_avatar_provider() override = default;

    QQuickImageResponse* requestImageResponse(const QString& id, const QSize& size) override;

private:
    const i_file_fs_path_maker& _path_maker;

    const i_image_component_storage& _image_component_storage;
    
    i_fs_image_worker& _image_storage;
};

#endif // T_QT_DEFAULT_AVATAR_PROVIDER_H
