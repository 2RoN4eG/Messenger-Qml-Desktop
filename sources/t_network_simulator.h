#ifndef T_NETWORK_SIMULATOR_H
#define T_NETWORK_SIMULATOR_H

#include "t_defines.h"


//

class t_peer_info_network {
    // self peer
    // conversations with
};


//

class i_network_simulator { };


//

class t_network_simulator
{
public:
    t_network_simulator();

    t_json_model_peers get_peers();

protected:
    t_url _get_peer_info { "qrc:/json/conversations.json" };
};

#endif // T_NETWORK_SIMULATOR_H
