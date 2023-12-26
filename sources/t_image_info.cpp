#include "t_image_info.h"

#include <iostream>
#include <sstream>

t_image_info::t_image_info(const t_url& url, const t_thumb_hash& thumb_hash)
    : _url { url }
    , _thumb_hash { thumb_hash }
{
}

// extra section

bool does_avatar_info_contain_url(const t_image_info& info) {
    return !info._url.isValid();
}

bool does_avatar_info_contain_thumb_hash(const t_image_info& info) {
    return !info._thumb_hash.empty();
}

bool does_avatar_info_contain_path(const t_image_info& info) {
    return !info._path.empty();
}

std::string do_print_string(const std::string_view name, const std::string_view& value, const bool print_string = true, const bool needs_end = false) {
    std::stringstream stream;
    stream << name << ": " << value << (needs_end ? "," : "") << std::endl;
    return stream.str();
}

void print_image_info(const t_image_info& avatar_info,
                      const bool print_url,
                      const bool print_thumb_hash,
                      const bool print_path) {
    std::cout << "t_image_info {" << std::endl
              << do_print_string("url",        avatar_info._url.toString().toStdString(), print_url,        true)
              << do_print_string("thumb_hash", avatar_info._thumb_hash,                   print_thumb_hash, true)
              << do_print_string("path",       avatar_info._path.generic_string(),        print_path,       false)
              << " }" << std::endl;
}
