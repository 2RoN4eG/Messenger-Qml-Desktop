#ifndef T_DEFINES_H
#define T_DEFINES_H

#include <filesystem>
#include <string>

#include <QUrl>
#include <QImage>

template <typename t_value>
class t_value_holder {
public:
    using t_value_type = t_value;

    t_value_holder(t_value value = 0)
        : _value { value }
    {
    }

    t_value_holder(const t_value_holder<t_value>& other) = default;
    t_value_holder<t_value>& operator=(const t_value_holder<t_value>& other) = default;

    t_value_holder(t_value_holder<t_value>&& other) = default;
    t_value_holder<t_value>& operator=(t_value_holder<t_value>&& other) = default;

    std::string to_string() const {
        return std::to_string(_value);
    }

protected:
    friend
        bool operator==(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
            return lhs._value == rhs._value;
        }

    friend
        bool operator<(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
            return lhs._value < rhs._value;
        }

    t_value _value {};
};


using t_qt_image                = QImage;
using t_qt_avatar               = t_qt_image;
using t_qt_photo                = t_qt_image;
using t_qt_size                 = QSize;
using t_qt_nickname             = QString;
using t_qt_url                  = QUrl;
using t_qt_message_timestamp    = qint64;

using t_fs_path                 = std::filesystem::path;
using t_fs_timestamp            = std::filesystem::file_time_type;
using t_fs_size                 = std::uintmax_t;
using t_fs_filename             = std::filesystem::path::string_type;
using t_fs_line                 = std::string;

using t_thumb_hash              = std::string;
using t_url                     = t_qt_url;
using t_bytes                   = std::string;

using t_nickname                = std::string;
using t_text                    = std::string;

using t_error                   = std::string;
using t_extra                   = std::string;

using t_peer_id                 = t_value_holder<int>;

using t_image_id                = t_value_holder<unsigned long long>;
using t_avatar_id               = t_image_id;
using t_photo_id                = t_image_id;

using t_image_bundle_id         = t_value_holder<long long>;
using t_avatar_bundle_id        = t_image_bundle_id;
using t_photo_bundle_id         = t_image_bundle_id;

using t_photo_bundle            = std::string;

using t_protocol                = std::string_view;
using t_hostname                = std::string_view;
using t_endpoint                = std::string;

using t_message_timestamp       = t_qt_message_timestamp;

enum t_avatar_type {
    t_default,
    t_squared,
    t_begin = t_default,
    t_end = t_squared
};


constexpr std::string_view to_string(const t_avatar_type avatar_type) {
    switch (avatar_type) {
    case t_avatar_type::t_default: return "default";
    case t_avatar_type::t_squared: return "squared";
    default: throw std::runtime_error { "avatar_type is unknown" };
    }
}

struct t_fs_meta
{
    t_fs_meta(const t_fs_path& path, t_fs_size size, t_fs_timestamp timestamp)
        : _path { path }
        , _size { size }
        , _timestamp { timestamp }
    {
    }

    friend
        bool operator<(const t_fs_meta& lhs, const t_fs_meta& rhs) {
            return lhs._timestamp < rhs._timestamp;
    }

    t_fs_path _path;
    t_fs_size _size;
    t_fs_timestamp _timestamp;
};

class t_json_model_avatar
{
public:
    t_json_model_avatar(t_thumb_hash&& thumb_hash, t_url&& url)
        : _thumb_hash { std::move(thumb_hash) }
        , _url { std::move(url) }
    {
    }

    t_json_model_avatar()
        : t_json_model_avatar { {}, {} }
    {
    }

    t_thumb_hash get_thumb_hash() const { return _thumb_hash; }

    t_url get_url() const { return _url; }

protected:
    t_thumb_hash _thumb_hash;
    t_url _url;
};

using t_json_model_avatars = std::vector<t_json_model_avatar>;

class t_json_model_message
{
public:
    t_json_model_message(t_text&& text, t_message_timestamp timestamp)
        : _text { std::move(text) }
        , _timestamp { timestamp }
    {
    }

    t_json_model_message()
        : t_json_model_message { {}, {} }
    {
    }

    t_text get_text() const { return _text; }

    t_message_timestamp get_timestamp() const { return _timestamp; }

protected:
    t_text _text;

    t_message_timestamp _timestamp;
};

using t_json_model_last_message = t_json_model_message;

class t_json_model_peer
{
public:
    t_json_model_peer(t_peer_id peer_id, t_nickname&& nickname, t_json_model_avatars&& avatars, t_json_model_last_message&& last_message)
        : _peer_id { peer_id }
        , _nickname { std::move(nickname) }
        , _avatars { std::move(avatars) }
        , _last_message { std::move(last_message) }
    {
    }

    t_json_model_peer()
        : t_json_model_peer { {}, {}, {}, {} }
    {
    }

    t_peer_id get_peer_id() const { return _peer_id; }

    t_nickname get_nickname() const { return _nickname; }

    t_json_model_avatars get_avatars() const { return _avatars; }

    t_json_model_last_message get_last_message() const { return _last_message; }

    t_json_model_avatar get_latest_avatar() const { return _avatars.front(); }

protected:
    t_peer_id                   _peer_id;
    t_nickname                  _nickname;
    t_json_model_avatars        _avatars;
    t_json_model_last_message   _last_message;
};

using t_json_model_peers = std::vector<t_json_model_peer>;

#endif // T_DEFINES_H
