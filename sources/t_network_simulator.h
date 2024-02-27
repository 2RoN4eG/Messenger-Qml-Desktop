#ifndef T_NETWORK_SIMULATOR_H
#define T_NETWORK_SIMULATOR_H

#include "t_defines.h"
#include "t_json_peer_parser.h"


class i_set_peer_info;


//

class i_network_simulator { };


//

class t_network_simulator
{
public:
    t_network_simulator(i_set_peer_info& peer_info_storage);

    void process_peer_infos();

protected:
    i_set_peer_info& _peer_info_storage;

    t_json_peer_info_processor _peer_info_parser;
};

#endif // T_NETWORK_SIMULATOR_H
