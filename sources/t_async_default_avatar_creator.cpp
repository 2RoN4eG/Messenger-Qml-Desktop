#include "t_async_default_avatar_creator.h"

#include <QImage>
#include <QPainter>

t_async_default_avatar_creator::t_async_default_avatar_creator(const t_image_id image_id)
    : _image_id { image_id }
{
}

void t_async_default_avatar_creator::run(const t_qt_nickname nickname, const t_qt_size size) {
    _image = { size, t_qt_image::Format_RGB32 };

    QPainter painter(&_image);

    painter.fillRect(_image.rect(), Qt::yellow);
    painter.drawText(_image.rect(), Qt::AlignCenter | Qt::AlignVCenter, nickname.front());

    emit created(_image_id);
}

t_image_id t_async_default_avatar_creator::get_image_id() const {
    return _image_id;
}

t_qt_image t_async_default_avatar_creator::get_image() const {
    return _image;
}
