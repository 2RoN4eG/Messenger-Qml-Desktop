#include "t_image_component.hpp"

#include <iostream>
#include <sstream>


t_image_component::t_image_component(const t_peer_id peer_id, const t_image_id image_id, const t_image_type_id image_type)
    : t_image_component { peer_id, image_id, image_type, {}, {} }
{
}

t_image_component::t_image_component(const t_peer_id peer_id, const t_image_id image_id, const t_image_type_id image_type, const t_url& url, const t_thumb_hash& thumb_hash)
    : _peer_id { peer_id }
    , _image_id { image_id }
    , _image_type_id { image_type }
    , _url { url }
    , _thumb_hash { thumb_hash }
{
}

bool operator<(const t_image_component& lhs, const t_image_component& rhs)
{
    if (lhs._image_id == rhs._image_id)
    {
        throw std::runtime_error { "image id must be unique for each image independent of kind (avatar, photo, sticker)" };
    }

    return lhs._image_id < rhs._image_id;
}


bool does_image_component_contain_url(const t_image_component& info)
{
    std::cout << "url is " << (info._url.isValid() ? "" : "not") << " valid " << std::endl;

    return info._url.isValid();
}

bool does_image_component_contain_thumb_hash(const t_image_component& info)
{
    return info._thumb_hash.size();
}


std::string do_print_string(const std::string_view name, const std::string_view& value, const bool print_string = true, const bool needs_end = false)
{
    std::stringstream stream;

    stream << name << ": " << value << (needs_end ? "," : "") << std::endl;

    return stream.str();
}

void print_image_component(const t_image_component& image_component, const bool print_url, const bool print_thumb_hash)
{
    std::cout << "t_image_component {" << std::endl
              << do_print_string("url",        image_component._url.toString().toStdString(), print_url,        true)
              << do_print_string("thumb_hash", image_component._thumb_hash,                   print_thumb_hash, true)
              << " }" << std::endl;
}
