#include "t_message_component_storage.hpp"

namespace
{
    struct t_finding_message_component_by_id
    {
    public:
        t_finding_message_component_by_id(const t_message_id message_id)
            : _message_id { message_id }
        {
        }
        
        bool operator()(const t_message_component& message) const {
            return _message_id == message._message_id;
        }

    private:
        const t_message_id _message_id;
    };

    struct t_finding_message_component_by_id_and_peer_id
    {
    public:
        t_finding_message_component_by_id_and_peer_id(const t_message_id message_id,
                                          const t_peer_id peer_id)
            : _message_id { message_id }
            , _peer_id { peer_id }
        {
        }
        
        bool operator()(const t_message_component& message) const {
            return _message_id == message._message_id && _peer_id == message._peer_id;
        }

    private:
        const t_message_id _message_id;

        const t_peer_id _peer_id;
    };

    inline const t_message_component& get_message_by_message_id(const t_message_components& message_components, const t_message_id message_id) {
        if (t_message_components::const_iterator it = std::find_if(message_components.begin(), message_components.end(), t_finding_message_component_by_id { message_id }); it != message_components.end()) {
            return *it;
        }

        throw std::runtime_error { "message does not exist by message_id { " + message_id.to_string() + " }" };
    }
}

namespace memory
{
    t_message_component_storage::t_message_component_storage(t_message_components& message_components)
        : _message_components { message_components }
    {
    }

    t_message_components& t_message_component_storage::message_components() const
    {
        return _message_components;
    }

    const size_t t_message_component_storage::size() const
    {
        return _message_components.size();
    }

    const t_message_id t_message_component_storage::operator[](size_t index) const
    {
        if (t_message_components_iterator iterator = std::next(_message_components.begin(), index); iterator != _message_components.end())
        {
            return iterator->_message_id;
        }

        throw std::runtime_error { "index is out of _message_components size" };
    }

    void t_message_component_storage::set_message_component(const t_message_id message_id,
                                                  const t_peer_id peer_id,
                                                  const t_message_text& text,
                                                  const t_message_timestamp timestamp)
    {
        set_message_component(message_id, peer_id, t_photo_id::none(), text, timestamp);
    }

    void t_message_component_storage::set_message_component(const t_message_id message_id,
                                                  const t_peer_id peer_id,
                                                  const t_photo_id photo_id,
                                                  const t_message_text& text,
                                                  const t_message_timestamp timestamp)
    {
        _message_components.emplace_back(message_id, peer_id, photo_id, text, timestamp);
    }

    t_peer_id t_message_component_storage::get_message_peer_id(const t_message_id message_id) const
    {
        const t_message_component& message = get_message_by_message_id(_message_components, message_id);

        return message._peer_id;
    }

    bool t_message_component_storage::does_message_photo_exist(const t_message_id message_id) const
    {
        const t_message_component& message = get_message_by_message_id(_message_components, message_id);

        return message._photo_id == t_photo_id::none();
    }

    t_photo_id t_message_component_storage::get_message_photo_id(const t_message_id message_id) const
    {
        const t_message_component& message = get_message_by_message_id(_message_components, message_id);

        return message._photo_id;
    }

    t_message_text t_message_component_storage::get_message_text(const t_message_id message_id) const
    {
        const t_message_component& message = get_message_by_message_id(_message_components, message_id);

        return message._text;
    }

    t_message_timestamp t_message_component_storage::get_message_timestamp(const t_message_id message_id) const
    {
        const t_message_component& message = get_message_by_message_id(_message_components, message_id);

        return message._timestamp;
    }
}
