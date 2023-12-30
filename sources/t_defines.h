#ifndef T_DEFINES_H
#define T_DEFINES_H

#include <filesystem>
#include <string>
#include <iostream>

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

using t_path                    = std::filesystem::path;
using t_timestamp               = std::filesystem::file_time_type;
using t_size                    = std::uintmax_t;
using t_filename                = std::filesystem::path::string_type;

using t_last_message_timestamp  = qint64;

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

using t_protocol                = std::string_view;
using t_hostname                = std::string_view;
using t_endpoint                = std::string;

enum t_avatar_type { t_default, t_squared, t_begin = t_default, t_end = t_squared };

constexpr std::string_view to_string(const t_avatar_type avatar_type) {
    switch (avatar_type) {
    case t_avatar_type::t_default: return "default";
    case t_avatar_type::t_squared: return "squared";
    default: throw std::runtime_error { "avatar_type is unknown" };
    }
}

struct t_fs_meta {
    t_path _path;
    t_size _size;
    t_timestamp _timestamp;

    t_fs_meta(const t_path& path, t_size size, t_timestamp timestamp)
        : _path { path }
        , _size { size }
        , _timestamp { timestamp }
    {
    }

    friend
        bool operator<(const t_fs_meta& lhs, const t_fs_meta& rhs) {
            return lhs._timestamp < rhs._timestamp;
    }
};

#endif // T_DEFINES_H
