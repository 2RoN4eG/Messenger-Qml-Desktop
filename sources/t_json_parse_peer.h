#ifndef T_JSON_PARSE_PEER_H
#define T_JSON_PARSE_PEER_H

#include "t_defines.h"

class i_fs;

// interface section

class i_json_parse_peer {
public:
    virtual t_json_model_peers operator()(const std::string_view json) const = 0;
};

class i_json_parse_peer_debug {
public:
    virtual t_json_model_peers from_file(const i_fs& fs, const t_fs_path& path = "") const = 0;
};

// class (interface implementation) section

class t_json_parse_peer : public i_json_parse_peer, public i_json_parse_peer_debug
{
public:
    t_json_model_peers operator()(const std::string_view json) const override;

    t_json_model_peers from_file(const i_fs& fs, const t_fs_path& path) const override;
};

#endif // T_JSON_PARSE_PEER_H
