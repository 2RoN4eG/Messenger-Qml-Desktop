#ifndef T_Ui_peer_context_PROVIDER_H
#define T_Ui_peer_context_PROVIDER_H

#include <QObject>
#include <QQuickItem>

#include "../t_defines.h"

class i_ui_mage_path_maker;
class i_peer_context_getter;
class i_peer_component_storage;

class t_qt_peer_preview_provider
    : public QQuickItem
{
    Q_OBJECT

public:
    t_qt_peer_preview_provider(const i_peer_context_getter* peer_context_getter = nullptr, const i_ui_mage_path_maker* ui_path_maker = nullptr);
    ~t_qt_peer_preview_provider() override = default;

    Q_INVOKABLE int size() const;
    
    Q_INVOKABLE QString latest_peer_avatar(int index) const;

    Q_INVOKABLE QString peer_nickname(int index) const;

    Q_INVOKABLE QString latest_message_preview(int index) const;

    Q_INVOKABLE QString latest_message_timestamp(int index) const;

    Q_INVOKABLE QString unread_messages(int index) const;

private:
    const i_peer_context_getter& _peer_context_getter;

    const i_peer_component_storage& _peer_component_storage;

    const t_peer_components& _peer_components;

    const i_ui_mage_path_maker& _ui_path_maker;
};

#endif // T_Ui_peer_context_PROVIDER_H
