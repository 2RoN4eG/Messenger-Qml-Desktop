#ifndef T_QT_PEER_CONVERSATION_PROVIDER_H
#define T_QT_PEER_CONVERSATION_PROVIDER_H

#include <QObject>
#include <QQuickItem>

#include "../t_defines.h"

class i_peer_context_getter;
class i_message_info_storage;

class t_peer_conversation_provider : public QQuickItem
{
    Q_OBJECT

public:
    t_peer_conversation_provider(const i_peer_context_getter* context_getter = nullptr);
    ~t_peer_conversation_provider() override = default;

    Q_INVOKABLE int size() const;

    Q_INVOKABLE QString latest_avatar_id(int index) const;

    Q_INVOKABLE QString message_peer_nickname(int index) const;

    Q_INVOKABLE QString message_photo(int index) const;

    Q_INVOKABLE QString message_text(int index) const;

    Q_INVOKABLE QString message_timestamp(int index) const;

private:
    const i_peer_context_getter& _context_getter;

    const i_message_info_storage& _message_info_storage;

    const t_message_infos& _message_infos;
};

#endif // T_QT_PEER_CONVERSATION_PROVIDER_H
