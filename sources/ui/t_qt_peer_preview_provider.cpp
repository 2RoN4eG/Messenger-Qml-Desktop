#include "t_qt_peer_preview_provider.h"

#include "../memory/t_peer_context_getter.h"
#include "../interfaces/i_peer_component_storage.hpp"

#include <iostream>

namespace
{
    inline const t_peer_component& get_peer_component(const t_peer_components& peer_components, const int index)
    {
        if (t_peer_components::iterator iterator = std::next(peer_components.begin(), index); iterator != peer_components.end())
        {
            return *iterator;
        }

        throw std::runtime_error { "peer_component does not exist by index" };
    }

    inline const t_peer_id get_peer_id(const t_peer_components& peer_components, const int index)
    {
        return get_peer_component(peer_components, index)._peer_id;
    }
}

t_qt_peer_preview_provider::t_qt_peer_preview_provider(const i_peer_context_getter* peer_context_getter, const i_ui_mage_path_maker* ui_path_maker)
    : _peer_context_getter { *peer_context_getter }
    , _peer_component_storage { _peer_context_getter.peer_component_storage() }
    , _peer_components { _peer_component_storage.get_peer_components() }
    , _ui_path_maker { *ui_path_maker }
{
}

int t_qt_peer_preview_provider::size() const
{
    return (int)_peer_components.size();
}

QString t_qt_peer_preview_provider::latest_peer_avatar(int index) const
{
    const t_peer_id peer_id = get_peer_id(_peer_components, index);

    try
    {
        const t_avatar_id avatar_id = _peer_context_getter.get_peer_latest_avatar_id(peer_id);

        return "image://avatars/" + QString::number(avatar_id.value());
    }
    catch (const std::exception& exception)
    {
        std::cerr << "exception: " << exception.what() << std::endl;
    }

    try
    {
        const t_avatar_id avatar_id = _peer_context_getter.get_peer_default_avatar_id(peer_id);

        return "image://default/" + QString::number(avatar_id.value());
    }
    catch (const std::exception& exception)
    {
        std::cerr << "exception: " << exception.what() << std::endl;
    }

    return "";
}

QString t_qt_peer_preview_provider::peer_nickname(int index) const
{
    const t_peer_id peer_id = get_peer_id(_peer_components, index);

    const t_nickname nickname = _peer_context_getter.get_peer_nickname(peer_id);

    return QString::fromStdString(nickname);
}

QString t_qt_peer_preview_provider::latest_message_preview(int index) const
{
    const t_peer_id peer_id = get_peer_id(_peer_components, index);
    
    _peer_context_getter.get_room_latest_message_preview(t_room_id::none());

    return "latest message preview for peer id " + QString::number(peer_id.value());
}

QString t_qt_peer_preview_provider::latest_message_timestamp(int index) const
{
    const t_peer_id peer_id = get_peer_id(_peer_components, index);

    return QString::number(index);
}

QString t_qt_peer_preview_provider::unread_messages(int index) const
{
    const t_peer_id peer_id = get_peer_id(_peer_components, index);

    return QString::number(index);
}
