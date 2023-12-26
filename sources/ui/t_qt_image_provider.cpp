#include "t_qt_image_provider.h"

#include "../t_defines.h"
#include "../t_path_aggregator.h"

#include "t_qt_image_response.h"

namespace
{
    t_image_id make_image_id(const QString& id)
    {
        return { id.toULongLong() };
    }
}

t_qt_image_provider::t_qt_image_provider(const i_image_fs_path_maker& path_maker,
                                   const i_image_info_storage& image_info_storage,
                                   i_fs_image_worker& image_storage)
    : _path_maker { path_maker }
    , _image_info_storage { image_info_storage }
    , _image_storage { image_storage }
{
}

QQuickImageResponse* t_qt_image_provider::requestImageResponse(const QString &id, const t_ui_size& size)
{
    t_qt_image_response* image_response = new t_qt_image_response(_image_storage, _path_maker, _image_info_storage, size);

    image_response->run(make_image_id(id));

    return image_response;
}
