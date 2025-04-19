#ifndef T_IMAGE_COMPONENT_HPP
#define T_IMAGE_COMPONENT_HPP

#include "t_defines.h"

class t_image_component
{
public:
    t_image_component(const t_peer_id peer_id, const t_image_id image_id, const t_image_type_id image_type);
    t_image_component(const t_peer_id peer_id, const t_image_id image_id, const t_image_type_id image_type, const t_url& url, const t_thumb_hash& thumb_hash);

    friend bool operator<(const t_image_component& lhs, const t_image_component& rhs);

public:
    [[maybe_unused]] const t_peer_id _peer_id;

    const t_image_id _image_id;

    [[maybe_unused]] const t_image_type_id _image_type_id;

    [[maybe_unused]] const t_image_bundle_id _image_bundle_id { t_image_bundle_id::none() };

    const t_url _url;

    const t_thumb_hash _thumb_hash;
};


using t_image_components                     = std::set<t_image_component>;
using t_constant_image_components_iterator   = t_image_components::const_iterator;
using t_image_components_iterator            = t_constant_image_components_iterator;
using t_image_component_cache                = t_image_components::const_iterator;


// bool operator<(const t_image_component& lhs, const t_image_component& rhs);

bool does_image_image_component_contain_url(const t_image_component& image);

bool does_image_image_component_contain_thumb_hash(const t_image_component& image);


void print_image_component_path(const t_image_component& image);

void print_image_component(const t_image_component& image, const bool print_url = true, const bool print_thumb_hash = true, const bool print_path = true);

#endif // T_IMAGE_COMPONENT_HPP
