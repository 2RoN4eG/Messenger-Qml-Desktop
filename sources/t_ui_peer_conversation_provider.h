#ifndef T_UI_PEER_CONVERSATION_PROVIDER_H
#define T_UI_PEER_CONVERSATION_PROVIDER_H

#include <QObject>
#include <QQuickItem>

#include "t_defines.h"

class i_messenger_context_getter;

class t_ui_peer_conversation_provider : public QQuickItem
{
    Q_OBJECT

public:
    t_ui_peer_conversation_provider(const i_messenger_context_getter* context_getter = nullptr);

    Q_INVOKABLE int count() const;

    Q_INVOKABLE QString peer_latest_avatar_id(int index) const;

    Q_INVOKABLE QString peer_message_nickname(int index) const;

    Q_INVOKABLE QString peer_message_photo(int index) const;

    Q_INVOKABLE QString peer_message_text(int index) const;

    Q_INVOKABLE QString peer_message_timestamp(int index) const;

private:
    const i_messenger_context_getter& _context_getter;

    const t_message_info_storage& _message_info_storage;
};

#endif // T_UI_PEER_CONVERSATION_PROVIDER_H
