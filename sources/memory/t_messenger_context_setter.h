#ifndef T_MESSENGER_CONTEXT_SETTER_H
#define T_MESSENGER_CONTEXT_SETTER_H

#include "../t_defines.h"
#include "../interface/i_image_info_storage.h"
#include "../interface/i_messenger_context_setter.h"

#include <QObject>


namespace memory
{

class t_messenger_context_setter : public i_messenger_context_setter
{
public:
    t_messenger_context_setter(t_peer_infos& peer_infos,
                               i_image_info_storage& image_info_storage,
                               t_message_info_storage& messages);


    void set_peer_info(const t_peer_id peer_id,
                       t_nickname&& nickname) override;

    void set_peer_avatar_image_info(const t_peer_id peer_id,
                                    const t_avatar_id avatar_id,
                                    const t_url& url,
                                    const t_thumb_hash& thumb_hash) override;

    void set_peer_message_info(const t_peer_id peer_id,
                               const t_message_text& text,
                               const t_message_timestamp timestamp) override;

    void set_peer_message_info(const t_peer_id peer_id,
                               const t_photo_id photo_id,
                               const t_message_text& text,
                               const t_message_timestamp timestamp) override;

    void set_peer_message_photo_image_info(const t_peer_id peer_id,
                                           const t_photo_id photo_id,
                                           const t_url& url,
                                           const t_thumb_hash& thumb_hash) override;

protected:
    t_peer_infos& _peer_infos;

    i_image_info_storage& _image_info_storage;

    t_message_info_storage& _messages;
};

} // namespace memory

#endif // T_MESSENGER_CONTEXT_SETTER_H
