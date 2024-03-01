#ifndef T_NETWORK_SIMULATOR_H
#define T_NETWORK_SIMULATOR_H

#include "t_defines.h"

#include "t_json_peer_info_parser.h"
#include "t_json_peer_message_processor.h"


class i_messenger_context_setter;

//

class i_network_simulator { };

//

class t_network_simulator
{
public:
    t_network_simulator(i_messenger_context_setter& peer_context_setter);

    void process_peer_info();

    void process_peer_message();

protected:
    i_messenger_context_setter& _peer_context_setter;

    t_image_id_generator _avatar_id_generator;

    t_json_peer_info_processor _peer_info_processor;

    t_image_id_generator& _photo_id_generator;

    t_json_peer_message_processor _peer_message_processor;

};

#endif // T_NETWORK_SIMULATOR_H
