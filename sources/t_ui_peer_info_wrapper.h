#ifndef T_UI_PEER_INFO_WRAPPER_H
#define T_UI_PEER_INFO_WRAPPER_H

#include <QObject>
#include <QQuickItem>
#include <QList>

#include "memory/t_messenger_context.h"


class t_ui_peer_info_wrapper : public QQuickItem
{
    Q_OBJECT

public:
    t_ui_peer_info_wrapper(t_peer_infos* peer_infos = nullptr, memory::t_peer_info_context* peer_info_storage = nullptr);
    
    Q_INVOKABLE int peer_amount() const;

    Q_INVOKABLE QString peer_id(int index) const;

    Q_INVOKABLE QString avatar_id(int index) const;

    Q_INVOKABLE QString nickname(int index) const;

    Q_INVOKABLE QString last_message(int index) const;

    Q_INVOKABLE QString last_message_timestamp(int index) const;

    Q_INVOKABLE QString messages_to_read(int index) const;

private:
    t_peer_infos& _peer_infos;

    memory::t_peer_info_context& _peer_info_storage;
};



#endif // T_UI_PEER_INFO_WRAPPER_H
