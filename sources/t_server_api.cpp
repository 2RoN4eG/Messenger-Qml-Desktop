#include "t_server_api.h"

#include <iostream>

std::string operator/(const std::string_view& lhs, const std::string_view& rhs) {
    std::string result;
    result.reserve(lhs.size() + 1 + rhs.size());

    result.append(lhs);
    result.append("/");
    result.append(rhs);

    return result;
}


t_protocol t_server_api::protocol() const {
    return "https:/";
}

t_hostname t_server_api::hostname() const {
    return "127.0.0.1";
}

t_endpoint t_server_api::endpoint() const {
    return "api";
}

t_endpoint t_server_api::peers_endpoint(const t_peer_id self_id) const {
    return protocol() / hostname() / endpoint() / "peers" / self_id.to_string();
}

t_endpoint t_server_api::conversation_endpoint(const t_peer_id self_id) const {
    return protocol() / hostname() / endpoint() / "conversation" / self_id.to_string();
}


void print_conversation_endpoint(const t_peer_id self_id) {
    const std::string& endpoint = t_server_api {}.conversation_endpoint(self_id);

    std::cout << std::setw(23) << "conversation_endpoint: " << endpoint << std::endl;
}

void print_peers_endpoint(const t_peer_id self_id) {
    const std::string& endpoint = t_server_api {}.peers_endpoint(self_id);

    std::cout << std::setw(23) << "peers_endpoint: " << endpoint << std::endl;
}

void print(const t_peer_id self_id) {
    print_conversation_endpoint(self_id);
    print_peers_endpoint(self_id);
}
