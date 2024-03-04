#ifndef T_DEFINES_H
#define T_DEFINES_H

#include <filesystem>
#include <string>
#include <set>


#include <QUrl>
#include <QImage>

#include "t_value.h"


enum t_avatar_type {
    t_default,
    t_squared,

    t_amount,
    t_begin = t_default,
    t_end = t_squared,

    t_default_avatar = t_default,
    t_squared_avatar = t_squared,
};

enum t_image_type {
    t_avatar_image,
    t_photo_image,
    t_stiker_image,

    t_default_avatar_image,
    t_squared_avatar_image,
};


using t_qt_image                = QImage;
using t_qt_avatar               = t_qt_image;
using t_qt_photo                = t_qt_image;
using t_qt_id                   = QString;
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

using t_id_type                 = unsigned long long;
using t_peer_id                 = t_value_holder<t_id_type>;

using t_image_id                = t_value_holder<t_id_type>;
using t_image_id_generator      = t_value_generator<t_id_type>;
using t_image_bundle_id         = t_value_holder<t_id_type>;

using t_avatar_id               = t_image_id;
using t_avatar_id_generator     = t_image_id_generator;
using t_avatar_bundle_id        = t_image_bundle_id;

using t_photo_id                = t_image_id;
using t_photo_id_generator      = t_image_id_generator;
using t_photo_bundle_id         = t_image_bundle_id;

using t_protocol                = std::string_view;
using t_hostname                = std::string_view;
using t_endpoint                = std::string;

using t_message_id              = t_value_holder<t_id_type>;
using t_message_id_generator    = t_value_generator<t_id_type>;
using t_message_bundle_id       = t_value_holder<t_id_type>;

using t_message_text            = std::string;
using t_message_timestamp       = t_qt_message_timestamp;


constexpr std::string_view to_string(const t_avatar_type avatar_type) {
    static_assert(t_avatar_type::t_amount == 2, "t_avatar_type::t_amount must be equal with 2");

    switch (avatar_type) {
    case t_avatar_type::t_default: return "default";
    case t_avatar_type::t_squared: return "squared";
    default: throw std::runtime_error { "avatar_type is unknown" };
    }
}

class t_fs_meta
{
public:
    t_fs_meta(const t_fs_path& path, t_fs_size size, t_fs_timestamp timestamp)
        : _path { path }
        , _size { size }
        , _timestamp { timestamp }
    {
    }

    friend inline
        bool operator<(const t_fs_meta& lhs, const t_fs_meta& rhs) {
            return lhs._timestamp < rhs._timestamp;
        }

public:
    t_fs_path _path;
    t_fs_size _size;
    t_fs_timestamp _timestamp;
};

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

    friend inline
        bool operator<(const t_peer_info& lhs, const t_peer_info& rhs) {
            return lhs._peer_id < rhs._peer_id;
        }


public:
    t_peer_id _peer_id;

    t_nickname _nickname;
};

class t_message
{
public:
    t_message(const t_peer_id peer_id, const t_message_text& text, t_message_timestamp timestamp)
        : t_message { peer_id, t_photo_id::none(), text, timestamp }
    {
    }

    t_message(const t_peer_id peer_id, const t_photo_id photo_id, const t_message_text& text, t_message_timestamp timestamp)
        : _peer_id { peer_id }
        , _photo_id { photo_id }
        , _text { text }
        , _timestamp { timestamp }
    {
    }

public:
    t_peer_id _peer_id {};

    t_message_id _message_id {};

    t_photo_id _photo_id {};

    t_message_text _text {};

    t_message_timestamp _timestamp {};
};

using t_peer_infos           = std::set<t_peer_info>;
using t_message_info_storage = std::vector<t_message>;

#endif // T_DEFINES_H
