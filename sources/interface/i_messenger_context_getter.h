#ifndef I_MESSENGER_CONTEXT_GETTER_H
#define I_MESSENGER_CONTEXT_GETTER_H

#include "../t_defines.h"
#include "../interface/i_image_info_storage.h"


class i_messenger_context_getter
{
public:
    virtual ~i_messenger_context_getter() = 0;


    virtual const t_peer_infos& peer_infos() const = 0;

    virtual const i_image_info_storage& image_info_storage() const = 0;

    virtual const t_message_info_storage& message_info_storage() const = 0;


    virtual const t_avatar_id get_latest_avatar_id(const t_peer_id peer_id) const = 0;

    virtual const t_avatar_id get_default_avatar_id(const t_peer_id peer_id) const = 0;

    virtual const t_nickname get_peer_nickname(const t_peer_id peer_id) const = 0;
};

#endif // I_MESSENGER_CONTEXT_GETTER_H
