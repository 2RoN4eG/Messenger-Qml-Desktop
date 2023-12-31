#ifndef T_UI_ASYNC_RESPONSE_DEFAULT_AVATAR_H
#define T_UI_ASYNC_RESPONSE_DEFAULT_AVATAR_H

#include "t_defines.h"

#include "t_async_default_avatar_creator.h"

#include <QQuickAsyncImageProvider>

class i_image_storage;
class i_image_info_storage;
class i_path_holder;

class QQuickTextureFactory;

class t_ui_async_response_default_avatar : public QQuickImageResponse
{
public:
    t_ui_async_response_default_avatar(const i_path_holder& path_holder,
                                        const i_image_info_storage& image_info_storage,
                                        i_image_storage& image_storage,
                                        const QSize& size);

    void run(const t_image_id image_id);

    QQuickTextureFactory *textureFactory() const override;

protected:
    void emit_finished();

    void run_async_image_creating(const t_image_id image_id, const t_qt_nickname nickname, const t_qt_size size);

protected slots:
    void on_image_created(const t_image_id image_id);

protected:
    t_image_creator_async_pointer _creating_command;

private:
    const i_path_holder& _path_holder;

    const i_image_info_storage& _image_info_storage;
    
    i_image_storage& _image_storage;

    QSize _size;

    t_qt_image _image;
};

#endif // T_UI_ASYNC_RESPONSE_DEFAULT_AVATAR_H
