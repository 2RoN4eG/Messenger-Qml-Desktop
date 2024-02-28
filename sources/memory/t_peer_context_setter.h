#ifndef T_PEER_CONTEXT_SETTER_H
#define T_PEER_CONTEXT_SETTER_H

#include "../t_defines.h"
#include "../interface/i_image_info_storage.h"
#include "../interface/i_peer_context_setter.h"

#include <QObject>


struct t_message {
    t_photo_id _photo_id {};

    t_message_text _text {};

    t_message_timestamp _timestamp {};

    t_message(const t_message_text& text, t_message_timestamp timestamp)
        : t_message { t_photo_id::none(), text, timestamp }
    {
    }

    t_message(const t_photo_id photo_id, const t_message_text& text, t_message_timestamp timestamp)
        : _photo_id { photo_id }
        , _text { text }
        , _timestamp { timestamp }
    {
    }
};

using t_messages = std::vector<t_message>;


namespace memory
{

class t_peer_context_setter : public QObject, public i_peer_context_setter // , public i_avatar_image_info // , public i_message_info
{
    Q_OBJECT

public:
    t_peer_context_setter(t_peer_infos& peer_infos,
                          i_image_info_storage& image_info_storage,
                          t_messages& messages);


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

    const t_avatar_id get_latest_avatar_id(const t_peer_id peer_id) const;

protected:
    t_peer_infos& _peer_infos;

    i_image_info_storage& _image_info_storage;

    t_messages& _messages;
};

} // namespace memory

#endif // T_PEER_CONTEXT_SETTER_H
