#include "t_image_creator_async.h"

#include <QImage>
#include <QPainter>

t_image_creator_async::t_image_creator_async(const t_avatar_id avatar_id)
    : _avatar_id { avatar_id }
{
}

void t_image_creator_async::run(const t_qt_nickname nickname, const t_qt_size size) {
    _avatar = { size, t_qt_image::Format_RGB32 };

    QPainter painter(&_avatar);

    painter.fillRect(_avatar.rect(), Qt::yellow);
    painter.drawText(_avatar.rect(), Qt::AlignCenter | Qt::AlignVCenter, nickname.front());

    emit created(_avatar_id);
}

t_avatar_id t_image_creator_async::get_avatar_id() const {
    return _avatar_id;
}

t_qt_avatar t_image_creator_async::get_avatar() const {
    return _avatar;
}
