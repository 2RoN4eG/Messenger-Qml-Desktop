#include "t_ui_peer_info_wrapper.h"

#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>

namespace {
    t_peer_info get_peer_info_by_index(const t_peer_infos& peer_infos, const int index) {
        if (t_peer_infos::iterator iterator = std::next(peer_infos.begin(), index); iterator != peer_infos.end()) {
            return *iterator;
        }

        throw std::runtime_error { "peer_info does not exist by index" };
    }

    t_peer_id get_peer_id_by_index(const t_peer_infos& peer_infos, const int index) {
        return get_peer_info_by_index(peer_infos, index)._peer_id;
    }

    t_nickname get_nickname_by_index(const t_peer_infos& peer_infos, const int index) {
        return get_peer_info_by_index(peer_infos, index)._nickname;
    }
}

t_ui_peer_info_wrapper::t_ui_peer_info_wrapper(t_peer_infos* peer_infos, memory::t_peer_info_context* peer_info_storage)
    : _peer_infos { *peer_infos }
    , _peer_info_storage { *peer_info_storage }
{
}

int t_ui_peer_info_wrapper::peer_amount() const {
    return (int)_peer_infos.size();
}

QString t_ui_peer_info_wrapper::peer_id(int index) const {
    const t_peer_id peer_id = get_peer_id_by_index(_peer_infos, index);

    return QString::number(peer_id.value());
}

QString t_ui_peer_info_wrapper::avatar_id(int index) const {
    const t_peer_id peer_id = get_peer_id_by_index(_peer_infos, index);

    const t_avatar_id avatar_id = _peer_info_storage.get_latest_avatar_id(peer_id);

    return "image://avatars/" + QString::number(avatar_id.value());
}

QString t_ui_peer_info_wrapper::nickname(int index) const {
    const t_nickname_view nickname = get_nickname_by_index(_peer_infos, index);

    return QString { nickname.data() };
}

QString t_ui_peer_info_wrapper::last_message(int index) const {
    return "peer_last_message, Index " + QString::number(index);
}

QString t_ui_peer_info_wrapper::last_message_timestamp(int index) const {
    return "peer_last_message_timestamp, Index " + QString::number(index);
}

QString t_ui_peer_info_wrapper::messages_to_read(int index) const {
    return "peer_message_amount, Index " + QString::number(index);
}

// memory::t_peer_info_storage* t_ui_binding_peer_info_context::get_peer_info_storage() const {
//     return _peer_info_storage;
// }

// void t_ui_binding_peer_info_context::set_peer_info_storage(memory::t_peer_info_storage* peer_info_storage) {
//     _peer_info_storage = peer_info_storage;
// }
