#include "t_qt_default_avatar_provider.h"

#include "../t_defines.h"
#include "t_qt_default_avatar_response.h"

namespace {
t_image_id make_image_id(const QString& id) {
    return { id.toULongLong() };
}
}

t_qt_default_avatar_provider::t_qt_default_avatar_provider(const i_image_fs_path_maker& path_holder,
                                                           const i_image_component_storage& image_component_storage,
                                                           i_fs_image_worker& image_storage)
    : _path_maker { path_holder }
    , _image_component_storage { image_component_storage }
    , _image_storage { image_storage }
{
}

QQuickImageResponse* t_qt_default_avatar_provider::requestImageResponse(const QString& id, const QSize& size) {
    t_qt_default_avatar_response* async_response = new t_qt_default_avatar_response(_path_maker,
                                                                                    _image_component_storage,
                                                                                    size,
                                                                                    _image_storage);
    const t_avatar_id avatar_id = make_image_id(id);

    async_response->run(avatar_id);

    return async_response;
}
