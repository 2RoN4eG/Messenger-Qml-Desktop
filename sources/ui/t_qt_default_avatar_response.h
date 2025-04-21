#ifndef T_QT_DEFAULT_AVATAR_RESPONSE_H
#define T_QT_DEFAULT_AVATAR_RESPONSE_H

#include "../t_defines.h"

#include "../async/t_qt_async_default_avatar_creator.h"

#include <QQuickAsyncImageProvider>

class i_fs_image_worker;
class i_file_fs_path_maker;
class i_image_component_storage;

class QQuickTextureFactory;

class t_qt_default_avatar_response : public QQuickImageResponse
{
public:
    t_qt_default_avatar_response(const i_file_fs_path_maker& path_maker,
                                 const i_image_component_storage& image_component_storage,
                                 const t_ui_size& size,
                                 i_fs_image_worker& image_storage);
    ~t_qt_default_avatar_response() override = default;

    void run(const t_image_id image_id);

    class QQuickTextureFactory* textureFactory() const override;

protected:
    void emit_finished();

    void run_async_image_creating(const t_image_id image_id, const t_ui_nickname nickname, const t_ui_size& size);

protected slots:
    void on_image_created(const t_image_id image_id);

protected:
    async::t_qt_default_avatar_creator_pointer _command;

private:
    const i_file_fs_path_maker& _path_maker;

    const i_image_component_storage& _image_component_storage;

    i_fs_image_worker& _image_storage;

    t_ui_size _size;

    t_ui_image _image;
};

#endif // T_QT_DEFAULT_AVATAR_RESPONSE_H
