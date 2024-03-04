#ifndef T_Ui_peer_context_PROVIDER_H
#define T_Ui_peer_context_PROVIDER_H

#include <QObject>
#include <QQuickItem>

#include "memory/t_messenger_context_getter.h"

class t_ui_peer_preview_provider : public QQuickItem
{
    Q_OBJECT

public:
    t_ui_peer_preview_provider(const memory::t_messenger_context_getter* peer_context_getter = nullptr);

    Q_INVOKABLE int count() const;

    Q_INVOKABLE QString peer_id(int index) const;

    Q_INVOKABLE QString avatar_id(int index) const;

    Q_INVOKABLE QString nickname(int index) const;

    Q_INVOKABLE QString last_message_preview(int index) const;

    Q_INVOKABLE QString last_message_timestamp(int index) const;

    Q_INVOKABLE QString messages_to_read(int index) const;

private:
    const memory::t_messenger_context_getter& _peer_context_getter;

    const t_peer_infos& _peer_infos;
};

#endif // T_Ui_peer_context_PROVIDER_H
