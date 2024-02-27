#ifndef T_DEFINES_H
#define T_DEFINES_H

#include <filesystem>
#include <string>
#include <set>


#include <QUrl>
#include <QImage>


template <typename t_value>
class t_value_holder
{
public:
    using t_value_type = t_value;

    t_value_holder(t_value value = {})
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

    const t_value value() const {
        return _value;
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

    friend
        bool operator>(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
            return lhs._value > rhs._value;
        }

    friend
        std::ostream& operator<<(std::ostream& stream, const t_value_holder<t_value>& holder) {
            stream << holder.value();
            return stream;
        }

    t_value _value {};
};


template <typename t_value>
class t_value_generator
{
public:
    t_value_generator()
        : _value {}
    {
    }

    const t_value_holder<t_value> get_value_and_generate_next() {
        return _value ++;
    }

    const t_value_holder<t_value> get_value_and_generate_previous() {
        return _value --;
    }

protected:
    t_value _value {};
};


using t_qt_image                = QImage;
using t_qt_avatar               = t_qt_image;
using t_qt_photo                = t_qt_image;
using t_qt_size                 = QSize;
using t_qt_nickname             = QString;
using t_qt_url                  = QUrl;
using t_qt_message_timestamp    = qint64;

using t_ui_image_id             = QString;

using t_fs_path                 = std::filesystem::path;
using t_fs_timestamp            = std::filesystem::file_time_type;
using t_fs_size                 = std::uintmax_t;
using t_fs_filename             = std::filesystem::path::string_type;
using t_fs_line                 = std::string;

using t_thumb_hash              = std::string;
using t_url                     = t_qt_url;
using t_bytes                   = std::string;

using t_nickname                = std::string;
using t_nickname_view           = std::string_view;
using t_text                    = std::string;

using t_error                   = std::string;
using t_extra                   = std::string;

using t_peer_id                 = t_value_holder<int>;

using t_image_id                = t_value_holder<unsigned long long>;
using t_image_id_generator      = t_value_generator<unsigned long long>;
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

class t_json_avatar_model
{
public:
    t_json_avatar_model(t_thumb_hash&& thumb_hash, t_url&& url)
        : _thumb_hash { std::move(thumb_hash) }
        , _url { std::move(url) }
    {
    }
    
    t_json_avatar_model()
        : t_json_avatar_model { {}, {} }
    {
    }

    t_thumb_hash get_thumb_hash() const { return _thumb_hash; }

    t_url get_url() const { return _url; }

protected:
    t_thumb_hash _thumb_hash;
    t_url _url;
};

using t_json_avatar_models = std::vector<t_json_avatar_model>;

class t_json_message_model
{
public:
    t_json_message_model(t_text&& text, t_message_timestamp timestamp)
        : _text { std::move(text) }
        , _timestamp { timestamp }
    {
    }

    t_json_message_model()
        : t_json_message_model { {}, {} }
    {
    }

    t_text get_text() const { return _text; }

    t_message_timestamp get_timestamp() const { return _timestamp; }

protected:
    t_text _text;

    t_message_timestamp _timestamp;
};

using t_json_model_last_message = t_json_message_model;

class t_json_peer_info_model
{
public:
    t_json_peer_info_model(t_peer_id peer_id, t_nickname&& nickname, t_json_avatar_models&& avatars, t_json_model_last_message&& last_message)
        : _peer_id { peer_id }
        , _nickname { std::move(nickname) }
        , _avatars { std::move(avatars) }
        , _last_message { std::move(last_message) }
    {
    }

    t_json_peer_info_model()
        : t_json_peer_info_model { {}, {}, {}, {} }
    {
    }

    t_peer_id peer_id() const { return _peer_id; }

    t_nickname nickname() const { return _nickname; }
    
    t_json_avatar_model avatar() const { return _avatars.front(); }

    t_json_model_last_message last_message() const { return _last_message; }

protected:
    t_peer_id                   _peer_id;

    t_nickname                  _nickname;

    t_json_avatar_models        _avatars;

    t_json_model_last_message   _last_message;
};

using t_json_peer_models = std::vector<t_json_peer_info_model>;

class t_peer_info
{
public:
    t_peer_info()
        : t_peer_info({}, {})
    {
    }

    t_peer_info(const t_peer_id peer_id, t_nickname&& nickname)
        : _peer_id { peer_id }
        , _nickname { std::move(nickname) }
    {
    }

public:
    t_peer_id _peer_id;

    t_nickname _nickname;
};
using t_peer_infos = std::set<t_peer_info>;

inline bool operator<(const t_peer_info& lhs, const t_peer_info& rhs) {
    return lhs._peer_id < rhs._peer_id;
}


#endif // T_DEFINES_H
