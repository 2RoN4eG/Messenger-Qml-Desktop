#ifndef T_IMAGE_INFO_H
#define T_IMAGE_INFO_H

#include "t_defines.h"

//

class t_image_info {
public:
    t_image_info(const t_url& url, const t_thumb_hash& thumb_hash);

    t_image_info(const t_image_info& avatar_info) = default;
    t_image_info& operator=(const t_image_info& avatar_info) = default;

    t_image_info(t_image_info&& avatar_info) = default;
    t_image_info& operator=(t_image_info&& avatar_info) = default;

public:
    t_url _url;

    t_thumb_hash _thumb_hash;

    t_path _path;
};

//

class t_image_info_extended {
public:
    t_image_info_extended(const t_image_id image_id, const t_peer_id peer_id, t_image_info&& image_info);

public:
    const t_image_id _image_id;

    const t_peer_id _peer_id;

    t_image_info _image_info;
};

bool operator<(const t_image_info_extended& lhs, const t_image_info_extended& rhs);

// extra section

bool does_avatar_info_contain_url(const t_image_info& info);

bool does_avatar_info_contain_thumb_hash(const t_image_info& info);

bool does_avatar_info_contain_path(const t_image_info& info);

void print_image_info_path(const t_image_info& avatar_info);

void print_image_info(const t_image_info& avatar_info, const bool print_url = true, const bool print_thumb_hash = true, const bool print_path = true);

//

#endif // T_IMAGE_INFO_H
