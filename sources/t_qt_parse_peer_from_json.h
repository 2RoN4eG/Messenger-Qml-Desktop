#ifndef T_QT_PARSE_PEER_FROM_JSON_H
#define T_QT_PARSE_PEER_FROM_JSON_H

#include "t_defines.h"

class t_avatar_model
{
public:
    t_avatar_model(t_thumb_hash&& thumb_hash, t_url&& url)
        : _thumb_hash { std::move(thumb_hash) }
        , _url { std::move(url) }
    {
    }

    t_avatar_model()
        : t_avatar_model { {}, {} }
    {
    }

    t_thumb_hash get_thumb_hash() const { return _thumb_hash; }

    t_url get_url() const { return _url; }

protected:
    t_thumb_hash _thumb_hash;
    t_url _url;
};

using t_avatar_models = std::vector<t_avatar_model>;

class t_last_message_model
{
public:
    t_last_message_model(t_text&& text, t_last_message_timestamp timestamp)
        : _text { std::move(text) }
        , _timestamp { timestamp }
    {
    }

    t_last_message_model()
        : t_last_message_model { {}, {} }
    {
    }

    t_text get_text() const { return _text; }

    t_last_message_timestamp get_timestamp() const { return _timestamp; }

protected:
    t_text _text;
    t_last_message_timestamp _timestamp;
};

class t_peer_model
{
public:
    t_peer_model(t_peer_id peer_id, t_nickname&& nickname, t_avatar_models&& avatars, t_last_message_model&& last_message)
        : _peer_id { peer_id }
        , _nickname { std::move(nickname) }
        , _avatars { std::move(avatars) }
        , _last_message { std::move(last_message) }
    {
    }

    t_peer_model()
        : t_peer_model { {}, {}, {}, {} }
    {
    }

    t_peer_id get_peer_id() const { return _peer_id; }

    t_nickname get_nickname() const { return _nickname; }

    t_avatar_models get_avatars() const { return _avatars; }

    t_last_message_model get_last_message() const { return _last_message; }

protected:
    t_peer_id               _peer_id;
    t_nickname              _nickname;
    t_avatar_models         _avatars;
    t_last_message_model    _last_message;
};

using t_peer_models = std::vector<t_peer_model>;


class t_qt_parse_peer_from_json
{
public:
    t_peer_models operator()(const std::string_view json) const;
};

#endif // T_QT_PARSE_PEER_FROM_JSON_H
