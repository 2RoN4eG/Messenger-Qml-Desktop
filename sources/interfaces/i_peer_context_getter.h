#ifndef I_PEER_CONTEXT_GETTER_H
#define I_PEER_CONTEXT_GETTER_H

#include "../t_defines.h"

class i_peer_component_storage;
class i_image_component_storage;
class i_message_component_storage;

class i_peer_context_getter
{
public:
    virtual ~i_peer_context_getter() = 0;


    virtual const i_peer_component_storage& peer_component_storage() const = 0;

    virtual const i_image_component_storage& image_component_storage() const = 0;

    virtual const i_message_component_storage& message_component_storage() const = 0;


    virtual const t_nickname get_peer_nickname(const t_peer_id peer_id) const = 0;

    virtual const bool does_peer_avatar_exist(const t_peer_id peer_id) const = 0;

    virtual const t_image_id get_peer_latest_avatar_id(const t_peer_id peer_id) const = 0;

    virtual const t_image_id get_peer_default_avatar_id(const t_peer_id peer_id) const = 0;


    virtual const bool does_peer_message_photo_exist(const t_message_id message_id) const = 0;

    virtual const t_photo_id get_peer_message_photo(const t_message_id message_id) const = 0;

    virtual const t_message_text get_peer_message_text(const t_message_id message_id) const = 0;

    virtual const t_message_timestamp get_peer_message_timestamp(const t_message_id message_id) const = 0;
    
    
    virtual const t_message_text get_room_latest_message_preview(const t_room_id room_id) const = 0;
    
    virtual const t_message_timestamp get_room_latest_message_timestamp(const t_room_id room_id) const = 0;
};

#endif // I_PEER_CONTEXT_GETTER_H
