#ifndef T_PEER_CONTEXT_SETTER_H
#define T_PEER_CONTEXT_SETTER_H

#include "../t_defines.h"
#include "../interfaces/i_peer_context_setter.h"

class i_peer_info_storage;
class i_image_info_storage;
class i_message_info_storage;

namespace memory
{

class t_peer_context_setter : public i_peer_context_setter
{
public:
    t_peer_context_setter(i_peer_info_storage& peer_info_storage,
                          i_image_info_storage& image_info_storage,
                          i_message_info_storage& message_info_storage);

    void set_peer_info(const t_peer_id peer_id,
                       t_nickname&& nickname) override;

    void set_peer_default_avatar_image_info(const t_peer_id peer_id,
                                            const t_avatar_id avatar_id) override;

    void set_peer_avatar_image_info(const t_peer_id peer_id,
                                    const t_avatar_id avatar_id,
                                    const t_url& url,
                                    const t_thumb_hash& thumb_hash) override;

    void set_peer_message_info(const t_peer_id peer_id,
                               const t_message_id message_id,
                               const t_message_text& text,
                               const t_message_timestamp timestamp) override;

    void set_peer_message_info(const t_peer_id peer_id,
                               const t_message_id message_id,
                               const t_photo_id photo_id,
                               const t_message_text& text,
                               const t_message_timestamp timestamp) override;

    void set_peer_message_photo_image_info(const t_peer_id peer_id,
                                           const t_photo_id photo_id,
                                           const t_url& url,
                                           const t_thumb_hash& thumb_hash) override;

protected:
    i_peer_info_storage& _peer_info_storage;

    i_image_info_storage& _image_info_storage;
    
    i_message_info_storage& _message_info_storage;
};

} // namespace memory

#endif // T_PEER_CONTEXT_SETTER_H
