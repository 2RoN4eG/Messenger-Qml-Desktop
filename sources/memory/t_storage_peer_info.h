#ifndef T_STORAGE_PEER_INFO_H
#define T_STORAGE_PEER_INFO_H

#include "../t_defines.h"
#include "../interfaces/i_storage_peer_info.h"

namespace memory
{
    class t_peer_info_storage : public i_peer_info_storage
    {
    public:
        t_peer_info_storage(t_peer_infos& peer_infos);

        void set_peer_info(const t_peer_id peer_id, t_nickname&& nickname) override;

        t_nickname get_nickname(const t_peer_id peer_id) const override;

        // TODO: Remove next 3 functions

        [[deprecated ("use external t_peer_infos& peer_infos to work as array")]]
        const t_peer_infos& get_peer_infos() const override;

        [[deprecated ("use external t_peer_infos& peer_infos to work as array")]]
        const size_t size() const override;

        [[deprecated ("use external t_peer_infos& peer_infos to work as array")]]
        const t_peer_id operator[](size_t index) const override;

    private:
        t_peer_infos& _peer_infos;
    };
}

#endif // T_STORAGE_PEER_INFO_H
