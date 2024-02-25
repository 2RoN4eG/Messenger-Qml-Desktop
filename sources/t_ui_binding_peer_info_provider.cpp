#include "t_ui_binding_peer_info_provider.h"

#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>


t_ui_binding_peer_info_provider::t_ui_binding_peer_info_provider() {
    // QQmlContext* context = QQmlEngine::contextForObject(this);
    // QQmlEngine::setContextForObject()
    // context->setContextProperty("", )
}

int t_ui_binding_peer_info_provider::peers() const {
    return 3;
}

QString t_ui_binding_peer_info_provider::id(int index) const {
    return QString::number(index);
}

QString t_ui_binding_peer_info_provider::avatar_id(int index) const {
    qDebug() << "peer_avatar_source index " << index;
    return "image://avatars/" + QString::number(index);
}

QString t_ui_binding_peer_info_provider::nickname(int index) const {
    return "Peer Nickname, Index " + QString::number(index);
}

QString t_ui_binding_peer_info_provider::last_message(int index) const {
    return "peer_last_message, Index " + QString::number(index);
}

QString t_ui_binding_peer_info_provider::last_message_timestamp(int index) const {
    return "peer_last_message_timestamp, Index " + QString::number(index);
}

QString t_ui_binding_peer_info_provider::messages_to_read(int index) const {
    return "peer_message_amount, Index " + QString::number(index);
}
