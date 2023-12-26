#ifndef T_QT_ASYNC_DEFAULT_AVATAR_CREATOR_H
#define T_QT_ASYNC_DEFAULT_AVATAR_CREATOR_H

#include "../t_defines.h"

#include <QObject>

class i_default_avatar_creator : public QObject
{
    Q_OBJECT

public:
    virtual ~i_default_avatar_creator() = 0;

    virtual void run(const t_image_id image_id, const t_ui_nickname& nickname, const t_ui_size& size) = 0;

    virtual t_image_id get_image_id() const = 0;

    virtual t_ui_image get_image() const = 0;

signals:
    void created(const t_image_id image_id);
};

namespace async
{
    class t_qt_async_default_avatar_creator : public i_default_avatar_creator
    {
    public:
        t_qt_async_default_avatar_creator() = default;
        ~t_qt_async_default_avatar_creator() = default;

        void run(const t_image_id image_id, const t_ui_nickname& nickname, const t_ui_size& size) override;

        t_image_id get_image_id() const override;

        t_ui_image get_image() const override;

    protected:
        t_image_id _image_id;

        t_ui_image _image;
    };

    using t_qt_default_avatar_creator_pointer = std::unique_ptr<t_qt_async_default_avatar_creator>;

    t_qt_default_avatar_creator_pointer make_qt_async_default_avatar_creator_pointer();
} // namespace async

#endif // T_QT_ASYNC_DEFAULT_AVATAR_CREATOR_H
