#ifndef T_UI_ASYNC_AVATAR_CREATING_RESPONSE_H
#define T_UI_ASYNC_AVATAR_CREATING_RESPONSE_H

#include "t_defines.h"

#include "t_image_creator_async.h"

#include <QQuickAsyncImageProvider>

class i_image_storage;
class i_image_info_storage;
class i_path_holder;

class QQuickTextureFactory;

class t_ui_async_avatar_creating_response : public QQuickImageResponse
{
public:
    t_ui_async_avatar_creating_response(const i_path_holder& path_holder,
                                        const i_image_info_storage& avatar_info_storage,
                                        i_image_storage& avatar_storage,
                                        const QSize& requested_size);

    void run(const t_avatar_id avatar_id);

    QQuickTextureFactory *textureFactory() const override;

protected:
    void emit_finished();

    void run_async_avatar_creating(const t_avatar_id avatar_id, const t_qt_nickname nickname, const t_qt_size size);

protected slots:
    void on_avatar_created(const t_avatar_id avatar_id);

protected:
    t_image_creator_async_pointer _creating_command;

private:
    const i_path_holder& _path_holder;

    const i_image_info_storage& _avatar_info_storage;
    
    i_image_storage& _avatar_storage;

    QSize _size;

    t_qt_avatar _avatar;
};

#endif // T_UI_ASYNC_AVATAR_CREATING_RESPONSE_H
