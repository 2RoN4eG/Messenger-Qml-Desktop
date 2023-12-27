#include "t_ui_squared_avatar_provider.h"

#include "t_defines.h"
#include "t_ui_async_avatar_downloading_response.h"
#include "t_path_maker.h"

namespace {
t_avatar_id make_avatar_id(const QString& id) {
    return { id.toULongLong() };
}
}

t_ui_squared_avatar_provider::t_ui_squared_avatar_provider(const i_path_holder& path_holder,
                                                           const i_image_info_storage& avatar_info_storage,
                                                           i_image_storage& avatar_storage)
    : _path_holder { path_holder }
    , _image_info_storage { avatar_info_storage }
    , _image_storage { avatar_storage }
{
}

QQuickImageResponse* t_ui_squared_avatar_provider::requestImageResponse(const QString &id, const QSize& requested_size) {
    t_ui_async_avatar_downloading_response* async_response = new t_ui_async_avatar_downloading_response(_path_holder, _image_info_storage, _image_storage, requested_size);
    async_response->run(make_avatar_id(id));
    return async_response;
}
