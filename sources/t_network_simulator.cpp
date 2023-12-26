#include "t_network_simulator.h"

#include <iostream>
#include "t_fs.h"
#include "t_json_peer_parser.h"

#include "QFile"

t_network_simulator::t_network_simulator() {
}

t_json_model_peers t_network_simulator::get_peers() {
    return t_json_peer_parser {}.from_file(t_fs {}, "/Users/2RoN4eG/Messenger-Qml-Desktop/json/peers.json");
}
