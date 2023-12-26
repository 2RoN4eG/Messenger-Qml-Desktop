#include "t_qt_async_default_avatar_creator.h"

#include <QImage>
#include <QPainter>

i_default_avatar_creator::~i_default_avatar_creator()
{
}

namespace async
{
    void t_qt_async_default_avatar_creator::run(const t_image_id image_id, const t_ui_nickname& nickname, const t_ui_size& size)
    {
        _image_id = image_id;
        _image = { size, t_ui_image::Format_RGB32 };

        QPainter painter(&_image);

        painter.fillRect(_image.rect(), Qt::yellow);
        painter.drawText(_image.rect(), Qt::AlignCenter | Qt::AlignVCenter, nickname.front());

        emit created(_image_id);
    }

    t_image_id t_qt_async_default_avatar_creator::get_image_id() const
    {
        return _image_id;
    }

    t_ui_image t_qt_async_default_avatar_creator::get_image() const
    {
        return _image;
    }


    t_qt_default_avatar_creator_pointer make_qt_async_default_avatar_creator_pointer()
    {
        return std::make_unique<async::t_qt_async_default_avatar_creator>();
    }
} // namespace async
