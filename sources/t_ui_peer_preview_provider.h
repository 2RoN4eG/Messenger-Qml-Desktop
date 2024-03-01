#ifndef T_Ui_peer_context_PROVIDER_H
#define T_Ui_peer_context_PROVIDER_H

#include <QObject>
#include <QQuickItem>

#include "memory/t_messender_context_setter.h"


class t_ui_peer_preview_provider : public QQuickItem
{
    Q_OBJECT

public:
    t_ui_peer_preview_provider(t_peer_info_storage* peer_infos = nullptr, memory::t_messenger_context_setter* peer_context_setter = nullptr);
    
    Q_INVOKABLE int count() const;

    Q_INVOKABLE QString peer_id(int index) const;

    Q_INVOKABLE QString avatar_id(int index) const;

    Q_INVOKABLE QString nickname(int index) const;

    Q_INVOKABLE QString last_message_preview(int index) const;

    Q_INVOKABLE QString last_message_timestamp(int index) const;

    Q_INVOKABLE QString messages_to_read(int index) const;

private:
    t_peer_info_storage& _peer_infos;

    memory::t_messenger_context_setter& _peer_context_setter;
};



#endif // T_Ui_peer_context_PROVIDER_H
