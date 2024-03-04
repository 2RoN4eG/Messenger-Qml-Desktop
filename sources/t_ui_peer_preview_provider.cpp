#include "t_ui_peer_preview_provider.h"

#include <iostream>
#include <QDebug>

namespace {
    const t_peer_info& get_peer_info(const t_peer_infos& peer_infos, const int index) {
        if (t_peer_infos::iterator iterator = std::next(peer_infos.begin(), index); iterator != peer_infos.end()) {
            return *iterator;
        }

        throw std::runtime_error { "peer_info does not exist by index" };
    }

    t_peer_id get_peer_id(const t_peer_infos& peer_infos, const int index) {
        return get_peer_info(peer_infos, index)._peer_id;
    }

    t_nickname_view get_nickname(const t_peer_infos& peer_infos, const int index) {
        return get_peer_info(peer_infos, index)._nickname;
    }
}


t_ui_peer_preview_provider::t_ui_peer_preview_provider(const memory::t_messenger_context_getter* peer_context_getter)
    : _peer_context_getter { *peer_context_getter }
    , _peer_infos { _peer_context_getter.peer_infos() }
{
}

int t_ui_peer_preview_provider::count() const {
    return (int)_peer_infos.size();
}

QString t_ui_peer_preview_provider::peer_id(int index) const {
    const t_peer_id peer_id = get_peer_id(_peer_infos, index);

    return QString::number(peer_id.value());
}

QString t_ui_peer_preview_provider::avatar_id(int index) const {
    const t_peer_id peer_id = get_peer_id(_peer_infos, index);

    try {
        const t_avatar_id avatar_id = _peer_context_getter.get_latest_avatar_id(peer_id);

        return "image://avatars/" + QString::number(avatar_id.value());
    }
    catch (const std::exception& exception) {
        const t_avatar_id avatar_id = _peer_context_getter.get_default_avatar_id(peer_id);

        return "image://default/" + QString::number(avatar_id.value());
    }
}

QString t_ui_peer_preview_provider::nickname(int index) const {
    const t_nickname_view nickname = get_nickname(_peer_infos, index);

    return QString { nickname.data() };
}

QString t_ui_peer_preview_provider::last_message_preview(int index) const {
    return "peer_last_message, Index " + QString::number(index);
}

QString t_ui_peer_preview_provider::last_message_timestamp(int index) const {
    return "peer_last_message_timestamp, Index " + QString::number(index);
}

QString t_ui_peer_preview_provider::messages_to_read(int index) const {
    return "peer_message_amount, Index " + QString::number(index);
}
