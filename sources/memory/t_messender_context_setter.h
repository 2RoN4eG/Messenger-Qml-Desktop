#ifndef T_MESSENDER_CONTEXT_SETTER_H
#define T_MESSENDER_CONTEXT_SETTER_H

#include "../t_defines.h"
#include "../interface/i_image_info_storage.h"
#include "../interface/i_messenger_context_setter.h"

#include <QObject>


class t_message {
public:
    t_message(const t_peer_id peer_id, const t_message_text& text, t_message_timestamp timestamp)
        : t_message { peer_id, t_photo_id::none(), text, timestamp }
    {
    }

    t_message(const t_peer_id peer_id, const t_photo_id photo_id, const t_message_text& text, t_message_timestamp timestamp)
        : _peer_id { peer_id }
        , _photo_id { photo_id }
        , _text { text }
        , _timestamp { timestamp }
    {
    }

public:
    t_peer_id _peer_id {};

    t_message_id _message_id {};

    t_photo_id _photo_id {};

    t_message_text _text {};

    t_message_timestamp _timestamp {};
};

using t_message_info_storage = std::vector<t_message>;


namespace memory
{

class t_messenger_context_setter : public QObject, public i_messenger_context_setter // , public i_avatar_image_info // , public i_message_info
{
    Q_OBJECT

public:
    t_messenger_context_setter(t_peer_info_storage& peer_infos,
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
    t_peer_info_storage& _peer_infos;

    i_image_info_storage& _image_info_storage;

    t_message_info_storage& _messages;
};

} // namespace memory

#endif // T_MESSENDER_CONTEXT_SETTER_H
