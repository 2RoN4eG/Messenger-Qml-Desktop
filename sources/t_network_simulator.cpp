#include "t_network_simulator.h"

#include "t_fs.h"

#include "json/t_json_peer_preview_parser.h"
#include "json/t_json_peer_message_processor.h"

#include "interfaces/i_peer_context_setter.h"

t_network_simulator::t_network_simulator(i_peer_context_setter& peer_context_setter,
                                         t_message_id_generator& message_id_generator,
                                         t_image_id_generator& image_id_generator)
    : _peer_context_setter { peer_context_setter }
    , _message_id_generator { message_id_generator }
    , _image_id_generator { image_id_generator }
{
    process_peer_info_file();

    process_peer_message_file();
}

void t_network_simulator::process_peer_info_file() {
    const std::string& json =
        t_read_file_as_single_line("/Users/2RoN4eG/Messenger-Qml-Desktop/json/peer_info.json");

    t_json_peer_preview_processor peer_info_processor { _peer_context_setter, _image_id_generator };

    peer_info_processor(json);
}

void t_network_simulator::process_peer_message_file() {
    const std::string& json =
        t_read_file_as_single_line("/Users/2RoN4eG/Messenger-Qml-Desktop/json/conversation_with.json");

    t_json_peer_message_processor peer_message_processor { _peer_context_setter, _message_id_generator, _image_id_generator };

    peer_message_processor(json);
}
