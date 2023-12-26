#ifndef T_NETWORK_SIMULATOR_H
#define T_NETWORK_SIMULATOR_H

#include "t_defines.h"

class i_peer_context_setter;

class t_network_simulator
{
public:
    t_network_simulator(i_peer_context_setter& peer_context_setter,
                        t_message_id_generator& message_id_generator,
                        t_image_id_generator& image_id_generator);

    void process_peer_info_file();

    void process_peer_message_file();

protected:
    i_peer_context_setter& _peer_context_setter;

    t_message_id_generator& _message_id_generator;

    t_image_id_generator& _image_id_generator;
};

#endif // T_NETWORK_SIMULATOR_H
