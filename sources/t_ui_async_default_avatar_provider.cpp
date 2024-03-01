#include "t_ui_async_default_avatar_provider.h"

#include "t_defines.h"
#include "t_ui_async_default_avatar_response.h"

namespace {
t_image_id make_image_id(const QString& id) {
    return { id.toULongLong() };
}
}

t_ui_async_provider_default_avatar::t_ui_async_provider_default_avatar(const i_path_maker& path_holder,
                                                                       const i_image_info_storage& image_info_storage,
                                                                       i_image_worker& image_storage)
    : _path_holder { path_holder }
    , _image_info_storage { image_info_storage }
    , _image_storage { image_storage }
{
}

QQuickImageResponse* t_ui_async_provider_default_avatar::requestImageResponse(const QString &id, const QSize& size) {
    t_ui_async_response_default_avatar* async_response = new t_ui_async_response_default_avatar(_path_holder,
                                                                                                _image_info_storage,
                                                                                                size,
                                                                                                _image_storage);
    async_response->run(make_image_id(id));
    return async_response;
}
