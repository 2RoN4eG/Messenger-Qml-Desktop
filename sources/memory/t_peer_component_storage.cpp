#include "t_peer_component_storage.h"

#include <iostream>


namespace
{
    struct t_finding_peer_component_by_peer_id
    {
        t_finding_peer_component_by_peer_id(const t_peer_id peer_id)
            : _peer_id { peer_id }
        {
        }

        bool operator()(const t_peer_component& peer_component) const
        {
            return peer_component._peer_id == _peer_id;
        }

        const t_peer_id _peer_id;
    };

    inline const t_peer_component& get_peer_component_by_peer_id(const t_peer_components& peer_components, const t_peer_id peer_id)
    {
        const t_finding_peer_component_by_peer_id finding_predicate { peer_id };

        if (t_peer_components_iterator it = std::find_if(peer_components.begin(), peer_components.end(), finding_predicate); it != peer_components.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_peer_component_by_peer_id: peer info does not exist, peer_id is " + peer_id.to_string() };
    }
}


namespace memory
{

t_peer_component_storage::t_peer_component_storage(t_peer_components& peer_components)
    : _peer_components { peer_components }
{
    std::cout << "peer components size is " << peer_components.size() << std::endl;
}

void t_peer_component_storage::set_peer_component(const t_peer_id peer_id, t_nickname&& nickname)
{
    std::cout << "set_peer_component peer_id is " << peer_id << ", nickname is " << nickname << std::endl;

    _peer_components.emplace(peer_id, std::move(nickname));
}

t_nickname t_peer_component_storage::get_nickname(const t_peer_id peer_id) const
{
    std::cout << "get_nickname(const t_peer_id peer_id { " << peer_id << " }) const" << std::endl;

    const t_peer_component& peer_component = get_peer_component_by_peer_id(_peer_components, peer_id);

    return peer_component._nickname;
}

const t_peer_components& t_peer_component_storage::get_peer_components() const
{
    return _peer_components;
}

}
