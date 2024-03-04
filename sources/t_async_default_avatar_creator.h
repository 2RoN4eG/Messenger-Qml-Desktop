#ifndef T_ASYNC_DEFAULT_AVATAR_CREATOR_H
#define T_ASYNC_DEFAULT_AVATAR_CREATOR_H

#include "t_defines.h"

#include <QObject>


class t_async_default_avatar_creator : public QObject
{
    Q_OBJECT

public:
    t_async_default_avatar_creator();

    void run(const t_image_id image_id, const t_qt_nickname nickname, const t_qt_size size);

    t_image_id get_image_id() const;

    t_qt_image get_image() const;

signals:
    void created(const t_image_id image_id);

protected:
    t_image_id _image_id;

    t_qt_image _image;
};

using t_image_creator_async_pointer = std::unique_ptr<t_async_default_avatar_creator>;

#endif // T_ASYNC_DEFAULT_AVATAR_CREATOR_H
