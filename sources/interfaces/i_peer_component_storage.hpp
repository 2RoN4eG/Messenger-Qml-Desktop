#pragma once

#include "../t_defines.h"


class i_peer_component_storage
{
public:
    virtual ~i_peer_component_storage() = 0;


    virtual void set_peer_component(const t_peer_id peer_id, t_nickname&& nickname) = 0;


    virtual t_nickname get_nickname(const t_peer_id peer_id) const = 0;


    virtual const t_peer_components& get_peer_components() const = 0;
};
