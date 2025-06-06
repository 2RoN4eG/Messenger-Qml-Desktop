#ifndef T_QT_IMAGE_PROVIDER_H
#define T_QT_IMAGE_PROVIDER_H

#include "../t_defines.h"

#include <QQuickAsyncImageProvider>

class i_image_component_storage;
class i_fs_image_worker;
class i_file_fs_path_maker;

class QQuickImageResponse;

class t_qt_image_provider : public QQuickAsyncImageProvider
{
public:
    t_qt_image_provider(i_fs_image_worker& image_storage, const i_file_fs_path_maker& path_maker, const i_image_component_storage& image_component_storage);
    ~t_qt_image_provider() override = default;

    QQuickImageResponse* requestImageResponse(const QString &id, const t_ui_size& size) override;

private:
    const i_file_fs_path_maker& _path_maker;

    const i_image_component_storage& _image_component_storage;
    
    i_fs_image_worker& _image_storage;
};

#endif // T_QT_IMAGE_PROVIDER_H
