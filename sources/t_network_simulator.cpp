#include "t_network_simulator.h"

#include "t_fs.h"

#include "interface/i_peer_info_storage.h"

t_network_simulator::t_network_simulator(i_set_peer_info& peer_info_storage)
    : _peer_info_storage { peer_info_storage }
    , _peer_info_parser { _peer_info_storage }
{
}

void t_network_simulator::process_peer_infos() {
    _peer_info_parser("/Users/2RoN4eG/Messenger-Qml-Desktop/json/peer_info_models.json", t_fs {});
}
