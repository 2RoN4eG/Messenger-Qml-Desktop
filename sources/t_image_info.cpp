#include "t_image_info.h"

#include <iostream>

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

void print_image_info_path(const t_image_info& avatar_info) {
    std::cout << "t_image_info { "
              << "path: " << avatar_info._path
              << " }" << std::endl;
}

void print_image_info(const t_image_info& avatar_info,
                       [[maybe_unused]] const bool print_url,
                       [[maybe_unused]] const bool print_thumb_hash,
                       [[maybe_unused]] const bool print_path) {
    std::cout << "t_image_info {"
              << " url: " << avatar_info._url.toString().toStdString()
              << ", thumb_hash: " << avatar_info._thumb_hash
              << ", path: " << avatar_info._path
              << " }" << std::endl;
}
