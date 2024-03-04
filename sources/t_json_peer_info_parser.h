#ifndef T_JSON_PEER_INFO_PARSER_H
#define T_JSON_PEER_INFO_PARSER_H

#include "t_defines.h"
#include "i_json_processor.h"

class i_fs;
class i_messenger_context_setter;


// class (interface implementation) section

class t_json_peer_info_processor : public i_json_processor
{
public:
    t_json_peer_info_processor(i_messenger_context_setter& messenger_context_getter, t_image_id_generator& avatar_id_generator);

    void operator()(const std::string_view json) const override;

private:
    i_messenger_context_setter& _peer_context_setter;

    t_image_id_generator& _avatar_id_generator;
};

#endif // T_JSON_PEER_INFO_PARSER_H
