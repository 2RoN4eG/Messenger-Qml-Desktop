#ifndef T_MESSENGER_CONTEXT_H
#define T_MESSENGER_CONTEXT_H

#include "../t_defines.h"
#include "../interface/i_image_info_storage.h"
#include "../interface/i_peer_info_storage.h"

#include <QObject>


namespace memory
{

class t_peer_info_context : public QObject, public i_set_peer_info
{
    Q_OBJECT

public:
    t_peer_info_context(t_peer_infos& peer_infos, i_image_info_storage& image_info_storage, t_image_id_generator& image_id_generator);

    void set_peer_info(const t_peer_id peer_id, t_nickname&& nickname) override;

    void set_image_info(const t_peer_id peer_id, const t_url& url, const t_thumb_hash& thumb_hash) override;

    t_avatar_id get_latest_avatar_id(const t_peer_id peer_id) const;

protected:
    t_peer_infos& _peer_infos;

    i_image_info_storage& _image_info_storage;

    t_image_id_generator& _image_id_generator;
};

} // namespace memory

#endif // T_MESSENGER_CONTEXT_H
