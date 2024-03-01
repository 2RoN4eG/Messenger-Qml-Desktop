#include "t_network_simulator.h"

#include "t_fs.h"

#include "interface/i_messenger_context_setter.h"

t_network_simulator::t_network_simulator(i_messenger_context_setter& peer_context_setter)
    : _peer_context_setter { peer_context_setter }
    , _peer_info_processor { _peer_context_setter, _avatar_id_generator }
    , _photo_id_generator { _avatar_id_generator }
    , _peer_message_processor { _peer_context_setter, _photo_id_generator }
{
}

void t_network_simulator::process_peer_info() {
    const std::string& json = t_fs {}.read_as_single_line("/Users/2RoN4eG/Messenger-Qml-Desktop/json/peer_info_models.json");

    _peer_info_processor(json);
}

void t_network_simulator::process_peer_message() {
    const std::string& json = t_fs {}.read_as_single_line("/Users/2RoN4eG/Messenger-Qml-Desktop/json/conversation_with_models.json");

    _peer_message_processor(json);
}
