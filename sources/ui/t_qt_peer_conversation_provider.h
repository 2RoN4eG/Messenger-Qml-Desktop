#ifndef T_QT_PEER_room_PROVIDER_H
#define T_QT_PEER_room_PROVIDER_H

#include <QObject>
#include <QQuickItem>

#include "../t_defines.h"

class i_peer_context_getter;
class i_message_component_storage;

class t_qt_peer_conversation_provider
    : public QQuickItem
{
    Q_OBJECT

public:
    t_qt_peer_conversation_provider(const i_peer_context_getter* context_getter = nullptr);
    ~t_qt_peer_conversation_provider() override = default;

    Q_INVOKABLE int size() const;

    Q_INVOKABLE QString latest_peer_avatar(int index) const;

    Q_INVOKABLE QString peer_nickname(int index) const;

    Q_INVOKABLE QString message_photo(int index) const;

    Q_INVOKABLE QString message_text(int index) const;

    Q_INVOKABLE QString message_timestamp(int index) const;

private:
    const i_peer_context_getter& _context_getter;

    const i_message_component_storage& _message_component_storage;

    const t_message_components& _message_components;
};

#endif // T_QT_PEER_room_PROVIDER_H
