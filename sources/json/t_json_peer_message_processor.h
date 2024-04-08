#ifndef T_JSON_PEER_MESSAGE_PROCESSOR_H
#define T_JSON_PEER_MESSAGE_PROCESSOR_H

#include "../t_defines.h"
#include "../interfaces/i_json_processor.h"


class i_peer_context_setter;

class t_json_peer_message_processor
    : public i_json_processor
{
public:
    t_json_peer_message_processor(i_peer_context_setter& peer_context_setter,
                                  t_message_id_generator& message_id_generator,
                                  t_image_id_generator& photo_id_generator);

    void operator()(const t_json_string_view json) const override;

private:
    i_peer_context_setter& _peer_context_setter;

    t_message_id_generator& _message_id_generator;

    t_image_id_generator& _photo_id_generator;
};

#endif // T_JSON_PEER_MESSAGE_PROCESSOR_H
