#include "t_ui_async_default_avatar_provider.h"

#include "t_defines.h"
#include "t_ui_async_default_avatar_response.h"
#include <iostream>

namespace {
t_image_id make_image_id(const QString& id) {
    return { id.toULongLong() };
}
}

t_ui_async_default_avatar_provider::t_ui_async_default_avatar_provider(const i_path_maker& path_holder,
                                                                       const i_image_info_storage& image_info_storage,
                                                                       i_image_worker& image_storage)
    : _path_holder { path_holder }
    , _image_info_storage { image_info_storage }
    , _image_storage { image_storage }
{
}

QQuickImageResponse* t_ui_async_default_avatar_provider::requestImageResponse(const QString& id, const QSize& size) {
    t_ui_async_response_default_avatar* async_response = new t_ui_async_response_default_avatar(_path_holder,
                                                                                                _image_info_storage,
                                                                                                size,
                                                                                                _image_storage);
    const t_avatar_id avatar_id = make_image_id(id);
    std::cout << "requestImageResponse() avatar_id is " << avatar_id << std::endl;
    async_response->run(avatar_id);
    return async_response;
}
