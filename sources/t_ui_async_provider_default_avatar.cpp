#include "t_ui_async_provider_default_avatar.h"

#include "t_defines.h"
#include "t_ui_async_response_default_avatar.h"

namespace {
t_image_id make_image_id(const QString& id) {
    return { id.toULongLong() };
}
}

t_ui_async_provider_default_avatar::t_ui_async_provider_default_avatar(const i_path_holder& path_holder,
                                                                       const i_image_info_storage& image_info_storage,
                                                                       i_image_storage& image_storage)
    : _path_holder { path_holder }
    , _image_info_storage { image_info_storage }
    , _image_storage { image_storage }
{
}

QQuickImageResponse* t_ui_async_provider_default_avatar::requestImageResponse(const QString &id, const QSize& size) {
    t_ui_async_response_default_avatar* async_response = new t_ui_async_response_default_avatar(_path_holder,
                                                                                                _image_info_storage,
                                                                                                _image_storage,
                                                                                                size);
    async_response->run(make_image_id(id));
    return async_response;
}
