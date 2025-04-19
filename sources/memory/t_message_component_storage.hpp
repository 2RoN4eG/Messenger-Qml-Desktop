#ifndef T_MESSAGE_component_STORAGE_H
#define T_MESSAGE_component_STORAGE_H

#include "../t_defines.h"

#include "../interfaces/i_message_component_storage.hpp"


namespace memory
{
    class t_message_component_storage
        : public i_message_component_storage
    {
    public:
        t_message_component_storage(t_message_components& message_components);

        ~t_message_component_storage() override = default;

        [[deprecated ("use external t_message_components& _message_components to work as array")]]
        t_message_components& message_components() const override;

        [[deprecated ("use external t_message_components& _message_components to work as array")]]
        const size_t size() const override;

        [[deprecated ("use external t_message_components& _message_components to work as array")]]
        const t_message_id operator[](size_t index) const override;

        void set_message_component(const t_message_id message_id,
                              const t_peer_id peer_id,
                              const t_message_text& text,
                              const t_message_timestamp timestamp) override;

        void set_message_component(const t_message_id message_id,
                              const t_photo_id photo_id,
                              const t_peer_id peer_id,
                              const t_message_text& text,
                              const t_message_timestamp timestamp) override;


        t_peer_id get_message_peer_id(const t_message_id message_id) const override;

        bool does_message_photo_exist(const t_message_id message_id) const override;

        t_photo_id get_message_photo_id(const t_message_id message_id) const override;

        t_message_text get_message_text(const t_message_id message_id) const override;

        t_message_timestamp get_message_timestamp(const t_message_id message_id) const override;

    private:
        t_message_components& _message_components;
    };
}

#endif // T_MESSAGE_component_STORAGE_H
