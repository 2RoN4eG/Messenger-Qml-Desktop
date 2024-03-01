#ifndef T_UI_ASYNC_DEFAULT_AVATAR_RESPONSE_H
#define T_UI_ASYNC_DEFAULT_AVATAR_RESPONSE_H

#include "t_defines.h"

#include "t_async_default_avatar_creator.h"

#include <QQuickAsyncImageProvider>

class i_image_worker;
class i_image_info_storage;
class i_path_maker;

class QQuickTextureFactory;

class t_ui_async_response_default_avatar : public QQuickImageResponse
{
public:
    t_ui_async_response_default_avatar(const i_path_maker& path_holder,
                                       const i_image_info_storage& image_info_storage,
                                       const t_qt_size& size,
                                       i_image_worker& image_storage);

    void run(const t_image_id image_id);

    QQuickTextureFactory *textureFactory() const override;

protected:
    void emit_finished();

    void run_async_image_creating(const t_image_id image_id, const t_qt_nickname nickname, const t_qt_size& size);

protected slots:
    void on_image_created(const t_image_id image_id);

protected:
    t_image_creator_async_pointer _creating_command;

private:
    const i_path_maker& _path_holder;

    const i_image_info_storage& _image_info_storage;
    
    i_image_worker& _image_storage;

    t_qt_size _size;

    t_qt_image _image;
};

#endif // T_UI_ASYNC_DEFAULT_AVATAR_RESPONSE_H
