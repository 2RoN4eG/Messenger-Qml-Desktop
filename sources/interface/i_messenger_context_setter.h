#ifndef i_peer_context_STORAGE_H
#define i_peer_context_STORAGE_H

#include "../t_defines.h"


class t_peer_info;

// Подумать над: стоит ли разделить контексты для пиров и сообщений?

class i_messenger_context_setter
{
public:
    virtual ~i_messenger_context_setter() = 0;


    virtual void set_peer_info(const t_peer_id peer_id, t_nickname&& nickname) = 0;

    virtual void set_peer_avatar_image_info(const t_peer_id peer_id,
                                            const t_avatar_id avatar_id,
                                            const t_url& url,
                                            const t_thumb_hash& thumb_hash) = 0;


    virtual void set_peer_message_info(const t_peer_id peer_id,
                                       const t_message_text& text,
                                       const t_message_timestamp timestamp) = 0;

    virtual void set_peer_message_info(const t_peer_id peer_id,
                                       const t_photo_id photo_id,
                                       const t_message_text& text,
                                       const t_message_timestamp timestamp) = 0;

    virtual void set_peer_message_photo_image_info(const t_peer_id peer_id,
                                                   const t_photo_id photo_id,
                                                   const t_url& url,
                                                   const t_thumb_hash& thumb_hash) = 0;
};

#endif // i_peer_context_STORAGE_H
