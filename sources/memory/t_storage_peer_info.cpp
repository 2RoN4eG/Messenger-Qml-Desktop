#include "t_storage_peer_info.h"

namespace {
    struct t_finding_peer_info_by_peer_id
    {
        t_finding_peer_info_by_peer_id(const t_peer_id peer_id)
            : _peer_id { peer_id }
        {
        }

        bool operator()(const t_peer_info& peer_info) const {
            return peer_info._peer_id == _peer_id;
        }

        const t_peer_id _peer_id;
    };

    inline const t_peer_info& get_peer_info_by_peer_id(const t_peer_infos& peer_infos, const t_peer_id peer_id)
    {
        const t_finding_peer_info_by_peer_id finding_predicate { peer_id };

        if (t_peer_infos_iterator it = std::find_if(peer_infos.begin(), peer_infos.end(), finding_predicate); it != peer_infos.end())
        {
            return *it;
        }

        throw std::runtime_error { "get_peer_info_by_peer_id: peer info does not exist by peer_id { " + peer_id.to_string() + " }" };
    }
}


namespace memory
{

t_peer_info_storage::t_peer_info_storage(t_peer_infos& peer_infos)
    : _peer_infos { peer_infos }
{
}

void t_peer_info_storage::set_peer_info(const t_peer_id peer_id, t_nickname&& nickname)
{
    _peer_infos.emplace(peer_id, std::move(nickname));
}

t_nickname t_peer_info_storage::get_nickname(const t_peer_id peer_id) const
{
    const t_peer_info& peer_info = get_peer_info_by_peer_id(_peer_infos, peer_id);

    return peer_info._nickname;
}

const t_peer_infos& t_peer_info_storage::get_peer_infos() const
{
    return _peer_infos;
}

const size_t t_peer_info_storage::size() const
{
    return _peer_infos.size();
}

const t_peer_id t_peer_info_storage::operator[](size_t index) const
{
    return std::next(_peer_infos.begin(), index)->_peer_id;
}

}
