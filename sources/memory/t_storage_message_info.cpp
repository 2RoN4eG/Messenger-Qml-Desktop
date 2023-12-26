#include "t_storage_message_info.h"

namespace
{
    struct t_finding_message_info_by_id
    {
    public:
        t_finding_message_info_by_id(const t_message_id message_id)
            : _message_id { message_id }
        {
        }
        
        bool operator()(const t_message_info& message) const {
            return _message_id == message._message_id;
        }

    private:
        const t_message_id _message_id;
    };

    struct t_finding_message_info_by_id_and_peer_id
    {
    public:
        t_finding_message_info_by_id_and_peer_id(const t_message_id message_id,
                                          const t_peer_id peer_id)
            : _message_id { message_id }
            , _peer_id { peer_id }
        {
        }
        
        bool operator()(const t_message_info& message) const {
            return _message_id == message._message_id && _peer_id == message._peer_id;
        }

    private:
        const t_message_id _message_id;

        const t_peer_id _peer_id;
    };

    inline const t_message_info& get_message_by_message_id(const t_message_infos& message_infos, const t_message_id message_id) {
        if (t_message_infos::const_iterator it = std::find_if(message_infos.begin(), message_infos.end(), t_finding_message_info_by_id { message_id }); it != message_infos.end()) {
            return *it;
        }

        throw std::runtime_error { "message does not exist by message_id { " + message_id.to_string() + " }" };
    }
}

namespace memory
{
    t_message_info_storage::t_message_info_storage(t_message_infos& message_infos)
        : _message_infos { message_infos }
    {
    }

    t_message_infos& t_message_info_storage::message_infos() const
    {
        return _message_infos;
    }

    const size_t t_message_info_storage::size() const
    {
        return _message_infos.size();
    }

    const t_message_id t_message_info_storage::operator[](size_t index) const
    {
        if (t_message_infos_iterator iterator = std::next(_message_infos.begin(), index); iterator != _message_infos.end())
        {
            return iterator->_message_id;
        }

        throw std::runtime_error { "index is out of _message_infos size" };
    }

    void t_message_info_storage::set_message_info(const t_message_id message_id,
                                                  const t_peer_id peer_id,
                                                  const t_message_text& text,
                                                  const t_message_timestamp timestamp)
    {
        set_message_info(message_id, peer_id, t_photo_id::none(), text, timestamp);
    }

    void t_message_info_storage::set_message_info(const t_message_id message_id,
                                                  const t_peer_id peer_id,
                                                  const t_photo_id photo_id,
                                                  const t_message_text& text,
                                                  const t_message_timestamp timestamp)
    {
        _message_infos.emplace_back(message_id, peer_id, photo_id, text, timestamp);
    }

    t_peer_id t_message_info_storage::get_message_peer_id(const t_message_id message_id) const
    {
        const t_message_info& message = get_message_by_message_id(_message_infos, message_id);

        return message._peer_id;
    }

    bool t_message_info_storage::does_message_photo_exist(const t_message_id message_id) const
    {
        const t_message_info& message = get_message_by_message_id(_message_infos, message_id);

        return message._photo_id == t_photo_id::none();
    }

    t_photo_id t_message_info_storage::get_message_photo_id(const t_message_id message_id) const
    {
        const t_message_info& message = get_message_by_message_id(_message_infos, message_id);

        return message._photo_id;
    }

    t_message_text t_message_info_storage::get_message_text(const t_message_id message_id) const
    {
        const t_message_info& message = get_message_by_message_id(_message_infos, message_id);

        return message._text;
    }

    t_message_timestamp t_message_info_storage::get_message_timestamp(const t_message_id message_id) const
    {
        const t_message_info& message = get_message_by_message_id(_message_infos, message_id);

        return message._timestamp;
    }
}
