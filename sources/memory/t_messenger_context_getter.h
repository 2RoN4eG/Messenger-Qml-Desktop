#ifndef T_MESSENGER_CONTEXT_GETTER_H
#define T_MESSENGER_CONTEXT_GETTER_H

#include "../t_defines.h"
#include "../interface/i_image_info_storage.h"
#include "../interface/i_messenger_context_getter.h"

#include <QObject>

namespace memory
{

class t_messenger_context_getter : public i_messenger_context_getter
{
public:
    t_messenger_context_getter(const t_peer_infos& peer_infos,
                               const i_image_info_storage& image_info_storage,
                               const t_message_info_storage& messages);

    const t_peer_infos& peer_infos() const override;

    const i_image_info_storage& image_info_storage() const override;

    const t_message_info_storage& message_info_storage() const override;


    const t_nickname get_peer_nickname(const t_peer_id peer_id) const override;

    const t_avatar_id get_default_avatar_id(const t_peer_id peer_id) const override;

    const t_avatar_id get_latest_avatar_id(const t_peer_id peer_id) const override;

protected:
    const t_peer_infos& _peer_infos;

    const i_image_info_storage& _image_info_storage;

    const t_message_info_storage& _messages;
};

} // namespace memory

#endif // T_MESSENGER_CONTEXT_GETTER_H
