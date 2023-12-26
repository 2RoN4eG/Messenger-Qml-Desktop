#ifndef T_NETWORK_SIMULATOR_H
#define T_NETWORK_SIMULATOR_H

#include "t_defines.h"

class t_peer_info {
    // self peer
    // conversations with
};

class i_network_simulator {
};

class t_network_simulator
{
public:
    t_network_simulator();

    t_peer_info get_peer_info();

protected:
    t_path _josn_peer;
};

#endif // T_NETWORK_SIMULATOR_H
