#ifndef T_STORAGE_PEER_component_H
#define T_STORAGE_PEER_component_H

#include "../t_defines.h"
#include "../interfaces/i_peer_component_storage.hpp"


namespace memory
{
    class t_peer_component_storage
        : public i_peer_component_storage
    {
    public:
        t_peer_component_storage(t_peer_components& peer_components);
        ~t_peer_component_storage() override = default;

        void set_peer_component(const t_peer_id peer_id, t_nickname&& nickname) override;

        t_nickname get_nickname(const t_peer_id peer_id) const override;


        const t_peer_components& get_peer_components() const override;

    private:
        t_peer_components& _peer_components;
    };
}

#endif // T_STORAGE_PEER_component_H
