#ifndef T_UI_BINDING_PEER_INFO_PROVIDER_H
#define T_UI_BINDING_PEER_INFO_PROVIDER_H

#include <QObject>
#include <QList>

class t_ui_binding_peer_info_provider : public QObject
{
    Q_OBJECT

public:
    t_ui_binding_peer_info_provider();

    Q_INVOKABLE int peers() const;

    Q_INVOKABLE QString id(int index) const;

    Q_INVOKABLE QString avatar_id(int index) const;

    Q_INVOKABLE QString nickname(int index) const;

    Q_INVOKABLE QString last_message(int index) const;

    Q_INVOKABLE QString last_message_timestamp(int index) const;

    Q_INVOKABLE QString messages_to_read(int index) const;
};



#endif // T_UI_BINDING_PEER_INFO_PROVIDER_H
