#ifndef T_PEER_CONTEXT_GETTER_H
#define T_PEER_CONTEXT_GETTER_H

#include "../t_defines.h"
#include "../interfaces/i_peer_context_getter.h"

class i_peer_info_storage;
class i_image_info_storage;
class i_message_info_storage;

namespace memory
{
    class t_peer_context_getter
        : public i_peer_context_getter
    {
    public:
        t_peer_context_getter(const i_peer_info_storage& peer_info_storage,
                              const i_image_info_storage& image_info_storage,
                              const i_message_info_storage& message_info_storage);
        ~t_peer_context_getter() override = default;


        const i_peer_info_storage& peer_info_storage() const override;

        const i_image_info_storage& image_info_storage() const override;

        const i_message_info_storage& message_info_storage() const override;


        const t_nickname get_peer_nickname(const t_peer_id peer_id) const override;

        const t_image_id get_peer_latest_avatar_id(const t_peer_id peer_id) const override;

        const t_image_id get_peer_default_avatar_id(const t_peer_id peer_id) const override;


        const bool does_peer_message_photo_exist(const t_message_id message_id) const override;

        const t_photo_id get_peer_message_photo(const t_message_id message_id) const override;

        const t_message_text get_peer_message_text(const t_message_id message_id) const override;

        const t_message_timestamp get_peer_message_timestamp(const t_message_id message_id) const override;

    protected:
        const i_peer_info_storage& _peer_info_storage;

        const i_image_info_storage& _image_info_storage;

        const i_message_info_storage& _message_info_storage;
    };
} // namespace memory

#endif // T_PEER_CONTEXT_GETTER_H
