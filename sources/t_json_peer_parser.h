#ifndef T_JSON_PEER_PARSER_H
#define T_JSON_PEER_PARSER_H

#include "t_defines.h"

class i_fs;
class i_set_peer_info;

// interface section

class i_json_peer_info_parser
{
public:
    virtual void operator()(const std::string_view json) const = 0;
};

class i_json_parse_peer_debug
{
public:
    virtual void operator()(const t_fs_path& path, const i_fs& fs) const = 0;
};

// class (interface implementation) section

class t_json_peer_info_processor : public i_json_peer_info_parser, public i_json_parse_peer_debug
{
public:
    t_json_peer_info_processor(i_set_peer_info& peer_info_storage);

    void operator()(const std::string_view json) const override;

    void operator()(const t_fs_path& path, const i_fs& fs) const override;

private:
    i_set_peer_info& _peer_info_storage;
};

void print_json_model_peers(t_json_peer_models&& peers);

#endif // T_JSON_PEER_PARSER_H
