#ifndef T_JSON_PEER_MESSAGE_PROCESSOR_H
#define T_JSON_PEER_MESSAGE_PROCESSOR_H

#include "t_defines.h"
#include "i_json_processor.h"


class i_fs;
class i_peer_context_setter;


// class (interface implementation) section

class t_json_peer_message_processor : public i_json_processor
{
public:
    t_json_peer_message_processor(i_peer_context_setter& peer_context_setter, t_image_id_generator& photo_id_generator);

    void operator()(const std::string_view json) const override;

private:
    i_peer_context_setter& _peer_context_setter;

    t_image_id_generator& _photo_id_generator;
};

#endif // T_JSON_PEER_MESSAGE_PROCESSOR_H
