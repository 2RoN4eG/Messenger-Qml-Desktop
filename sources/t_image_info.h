#ifndef T_IMAGE_INFO_H
#define T_IMAGE_INFO_H

#include "t_defines.h"

class t_image_info
{
public:
    t_image_info(const t_peer_id peer_id, const t_image_id image_id, const t_image_type_id image_type);
    t_image_info(const t_peer_id peer_id, const t_image_id image_id, const t_image_type_id image_type, const t_url& url, const t_thumb_hash& thumb_hash);

    friend bool operator<(const t_image_info& lhs, const t_image_info& rhs);

public:
    const t_peer_id _peer_id;

    const t_image_id _image_id;
    
    const t_image_type_id _image_type_id;

    const t_image_bundle_id _image_bundle_id { t_image_bundle_id::none() };

    const t_url _url;

    const t_thumb_hash _thumb_hash;
};

// bool operator<(const t_image_info& lhs, const t_image_info& rhs);

bool does_image_info_contain_url(const t_image_info& info);

bool does_image_info_contain_thumb_hash(const t_image_info& info);


void print_image_info_path(const t_image_info& avatar_info);

void print_image_info(const t_image_info& image_info, const bool print_url = true, const bool print_thumb_hash = true, const bool print_path = true);

#endif // T_IMAGE_INFO_H
