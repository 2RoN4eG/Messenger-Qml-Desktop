#ifndef T_UI_PEER_CONVERSATION_PROVIDER_H
#define T_UI_PEER_CONVERSATION_PROVIDER_H

#include <QObject>
#include <QQuickItem>

#include "memory/t_peer_context_setter.h"


class t_ui_peer_conversation_provider : public QQuickItem
{
    Q_OBJECT

public:
    t_ui_peer_conversation_provider(const t_messages* messages = nullptr);

    Q_INVOKABLE int count() const;

    Q_INVOKABLE QString peer_message_nickname(int index) const;

    Q_INVOKABLE QString peer_message_photo(int index) const;

    Q_INVOKABLE QString peer_message_text(int index) const;

    Q_INVOKABLE QString peer_message_timestamp(int index) const;

private:
    const t_messages& _messages;
};

#endif // T_UI_PEER_CONVERSATION_PROVIDER_H
