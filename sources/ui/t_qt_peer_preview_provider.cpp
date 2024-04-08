#include "t_qt_peer_preview_provider.h"

#include "../t_defines.h"

#include "../memory/t_peer_context_getter.h"
#include "../interfaces/i_storage_peer_info.h"
#include "../t_ui_image_path_maker.h"

#include <iostream>

namespace {
    const t_peer_info& get_peer_info(const t_peer_infos& peer_infos, const int index) {
        if (t_peer_infos::iterator iterator = std::next(peer_infos.begin(), index); iterator != peer_infos.end()) {
            return *iterator;
        }

        throw std::runtime_error { "peer_info does not exist by index" };
    }
}

t_peer_preview_provider::t_peer_preview_provider(const i_peer_context_getter* peer_context_getter, const i_ui_mage_path_maker* ui_path_maker)
    : _peer_context_getter { *peer_context_getter }
    , _peer_info_storage { _peer_context_getter.peer_info_storage() }
    , _ui_path_maker { *ui_path_maker }
{
}

int t_peer_preview_provider::size() const
{
    return (int)_peer_info_storage.size();
}

QString t_peer_preview_provider::latest_peer_avatar(int index) const
{
    const t_peer_id peer_id = _peer_info_storage[index];

    try
    {
        const t_avatar_id avatar_id = _peer_context_getter.get_peer_latest_avatar_id(peer_id);

        return "image://avatars/" + QString::number(avatar_id.value());
    }
    catch (const std::exception& exception)
    {
        std::cerr << "exception: " << exception.what() << std::endl;

        const t_avatar_id avatar_id = _peer_context_getter.get_peer_default_avatar_id(peer_id);

        return "image://default/" + QString::number(avatar_id.value());
    }
}

QString t_peer_preview_provider::peer_nickname(int index) const
{
    const t_peer_id peer_id = _peer_info_storage[index];

    const t_nickname nickname = _peer_context_getter.get_peer_nickname(peer_id);

    return QString::fromStdString(nickname);
}

QString t_peer_preview_provider::latest_message_preview(int index) const
{
    return "peer_last_message, Index " + QString::number(index);
}

QString t_peer_preview_provider::latest_message_timestamp(int index) const
{
    return QString::number(index);
}

QString t_peer_preview_provider::unread_messages(int index) const
{
    return "peer_message_amount, Index " + QString::number(index);
}
