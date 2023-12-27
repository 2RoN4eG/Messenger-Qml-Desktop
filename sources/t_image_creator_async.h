#ifndef T_IMAGE_CREATOR_ASYNC_H
#define T_IMAGE_CREATOR_ASYNC_H

#include "t_defines.h"

#include <QObject>
#include <QImage>

class QString;
class QSize;

class t_image_creator_async : public QObject
{
    Q_OBJECT

public:
    t_image_creator_async(const t_avatar_id avatar_id);

    void run(const t_qt_nickname nickname, const t_qt_size size);

    t_avatar_id get_avatar_id() const;

    t_qt_avatar get_avatar() const;

signals:
    void created(const t_avatar_id avatar_id);

protected:
    t_qt_avatar _avatar;

    const t_avatar_id _avatar_id;
};

using t_image_creator_async_pointer = std::unique_ptr<t_image_creator_async>;

#endif // T_IMAGE_CREATOR_ASYNC_H
