#ifndef T_SERVER_API_H
#define T_SERVER_API_H

#include "t_defines.h"

class t_server_api
{
    t_protocol protocol() const;

    t_hostname hostname() const;

    t_endpoint endpoint() const;

public:
    t_endpoint conversation_endpoint(const t_peer_id self_id) const;

    t_endpoint peers_endpoint(const t_peer_id self_id) const;
};

void print(const t_peer_id self_id);

#endif // T_SERVER_API_H
