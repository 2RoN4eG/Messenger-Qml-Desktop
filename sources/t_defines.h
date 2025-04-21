#ifndef T_DEFINES_H
#define T_DEFINES_H

#include <filesystem>
#include <string>
#include <set>

#include <QUrl>
#include <QImage>

#include "t_value.h"

enum /*class*/ t_avatar_type_id /*: size_t*/
{
    t_default_avatar    = 0,
    t_squared_avatar    = 1,
    t_rounded_avatar    = 2,

    t_avatar_type_amount
};

enum class t_image_type_id /*: size_t*/
{
    t_default_avatar = t_avatar_type_id::t_default_avatar,
    t_squared_avatar = t_avatar_type_id::t_squared_avatar,
    t_rounded_avatar = t_avatar_type_id::t_rounded_avatar,

    t_photo,
    t_stiker,

    t_image_type_amount
};

using t_ui_string                   = QString;
using t_ui_image                    = QImage;
using t_ui_id                       = QString;
using t_ui_size                     = QSize;
using t_ui_nickname                 = QString;
using t_ui_message_timestamp        = qint64;
using t_ui_path                     = t_ui_string;
using t_ui_image_id                 = t_ui_path;

using t_qt_url                      = QUrl;

using t_fs_path                     = std::filesystem::path;
using t_fs_timestamp                = std::filesystem::file_time_type;
using t_fs_size                     = std::uintmax_t;
using t_fs_filename                 = std::filesystem::path::string_type;
using t_fs_line                     = std::string;

using t_thumb_hash                  = std::string;
using t_url                         = t_qt_url;
using t_bytes                       = std::string;

using t_nickname                    = std::string;
using t_text                        = std::string;

using t_error                       = std::string;
using t_extra                       = std::string;

using t_id_type                     = unsigned long long;
using t_peer_id                     = t_value_holder<t_id_type>;

using t_image_id                    = t_value_holder<t_id_type>;
using t_image_id_generator          = t_value_generator<t_id_type>;
using t_image_bundle_id             = t_value_holder<t_id_type>;

using t_avatar_id                   = t_image_id;
using t_avatar_id_generator         = t_image_id_generator;
using t_avatar_bundle_id            = t_image_bundle_id;

using t_default_avatar_id           = t_avatar_id;

using t_photo_id                    = t_image_id;
using t_photo_id_generator          = t_image_id_generator;
using t_photo_bundle_id             = t_image_bundle_id;

using t_message_id                  = t_value_holder<t_id_type>;
using t_message_id_generator        = t_value_generator<t_id_type>;
using t_message_bundle_id           = t_value_holder<t_id_type>;

using t_room_id                     = t_value_holder<t_id_type>;
using t_room_id_generator           = t_value_generator<t_id_type>;

using t_protocol                    = std::string_view;
using t_hostname                    = std::string_view;
using t_endpoint                    = std::string;

using t_message_text                = std::string;
using t_message_timestamp           = t_ui_message_timestamp;

constexpr std::string_view to_string(const t_avatar_type_id avatar_type_id)
{
    static_assert(static_cast<size_t>(t_avatar_type_id::t_avatar_type_amount) == size_t { 3 }, "t_avatar_type::t_amount must be equal with 3");

    switch (avatar_type_id)
    {
    case t_avatar_type_id::t_default_avatar:
        return "default";
    case t_avatar_type_id::t_squared_avatar:
        return "squared";
    case t_avatar_type_id::t_rounded_avatar:
        return "rounded";
    default:
        throw std::runtime_error { "avatar_type_id is undefined" };
    }
}

constexpr std::string image_type_id_to_string(const t_image_type_id image_type_id)
{
    static_assert(static_cast<size_t>(t_image_type_id::t_image_type_amount) == size_t { 5 }, "t_image_type_id::t_amount must be equal with 5");

    switch (image_type_id)
    {
    case t_image_type_id::t_default_avatar: return "default_avatar";
    case t_image_type_id::t_squared_avatar: return "squared_avatar";
    case t_image_type_id::t_rounded_avatar: return "rounded_avatar";
    case t_image_type_id::t_photo:          return "photo";
    case t_image_type_id::t_stiker:         return "stiker";
    default: throw std::runtime_error { "image_type_id is undefined" };
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

public:
    t_fs_path _path;

    t_fs_size _size;

    t_fs_timestamp _timestamp;
};

inline bool operator<(const t_fs_meta& lhs, const t_fs_meta& rhs)
{
    return lhs._timestamp < rhs._timestamp;
}

using t_fs_metas                    = std::set<t_fs_meta>;

class t_peer_component
{
public:
    t_peer_component()
        : t_peer_component({}, {})
    {
    }

    t_peer_component(const t_peer_id peer_id, t_nickname&& nickname)
        : _peer_id { peer_id }
        , _nickname { std::move(nickname) }
    {
    }

    friend inline bool operator<(const t_peer_component& lhs, const t_peer_component& rhs)
    {
        return lhs._peer_id < rhs._peer_id;
    }

public:
    t_peer_id _peer_id;

    t_nickname _nickname;
};

using t_peer_components             = std::set<t_peer_component>;

using t_peer_components_iterator    = t_peer_components::const_iterator;

class t_message_component
{
public:
    t_message_component(const t_message_id message_id,
                        const t_peer_id peer_id,
                        const t_message_text& text,
                        const t_message_timestamp timestamp)
        : t_message_component { message_id, peer_id, t_photo_id::none(), text, timestamp }
    {
    }

    t_message_component(const t_message_id message_id,
                        const t_peer_id peer_id,
                        const t_photo_id photo_id,
                        const t_message_text& text,
                        const t_message_timestamp timestamp)
        : _message_id { message_id }
        , _peer_id { peer_id }
        , _photo_id { photo_id }
        , _text { text }
        , _timestamp { timestamp }
    {
    }

public:
    t_room_id _room_id {};

    t_message_id _message_id {};

    t_peer_id _peer_id {};

    t_photo_id _photo_id {};

    t_message_text _text {};

    t_message_timestamp _timestamp {};
};

using t_message_components          = std::vector<t_message_component>;

using t_message_components_iterator = std::vector<t_message_component>::iterator;

constexpr const char* t_messenger_root_path = "/Users/2RoN4eG/Messenger/MacOS";

#endif // T_DEFINES_H
