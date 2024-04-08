#include "t_path_aggregator.h"

namespace
{
    constexpr const char* t_avatars = "avatars";
    constexpr const char* t_photos  = "photos";
    constexpr const char* t_stikers = "stikers";
}


i_image_fs_path_maker::~i_image_fs_path_maker()
{
}

// class section

t_fs_common_paths::t_fs_common_paths(const t_fs_path& root, const t_peer_id& self)
    : _root { root }
    , _self_peer_id { self }
{
}

//

t_fs_path t_fs_common_paths::get_fs_path_for_self() const { return _root / _self_peer_id; }

t_fs_path t_fs_common_paths::get_fs_path_for_peer(const t_peer_id peer_id) const { return get_fs_path_for_self() / peer_id; }

//

t_fs_path t_fs_common_paths::get_fs_path_for_avatar(const t_peer_id peer_id) const { return get_fs_path_for_peer(peer_id) / t_avatars; }

t_fs_path t_fs_common_paths::get_fs_path_for_avatar(const t_peer_id peer_id, const t_avatar_type_id avatar_type) const { return get_fs_path_for_avatar(peer_id) / to_string(avatar_type); }

t_fs_path t_fs_common_paths::get_fs_path_for_avatar(const t_peer_id peer_id, const t_avatar_type_id avatar_type, const t_fs_filename& filename) const { return get_fs_path_for_avatar(peer_id, avatar_type) / filename; }

//

t_fs_path t_fs_common_paths::get_fs_path_for_photo(const t_peer_id peer_id) const { return get_fs_path_for_peer(peer_id) / t_photos; }

t_fs_path t_fs_common_paths::get_fs_path_for_photo(const t_peer_id peer_id, const t_fs_filename& filename) const { return get_fs_path_for_photo(peer_id) / filename; }

t_fs_path t_fs_common_paths::get_fs_path_for_photo(const t_peer_id peer_id, const t_photo_bundle_id& bundle_id, const t_fs_filename& filename) const { return get_fs_path_for_photo(peer_id) / bundle_id / filename; }

//

t_fs_path t_fs_common_paths::get_fs_path_for_stiker(const t_fs_filename& filename) const { return _root / t_stikers / filename; }

// make section (fabric methods section)

t_fs_common_paths make_common_path(const t_fs_path& root, const t_peer_id& self) { return t_fs_common_paths { root, self }; }

// test section (to avoid wasting time is located here)

void test_get_fs_path_for_avatar(const i_avatar_fs_path& avatar_path, const t_peer_id peer_id, const t_avatar_type_id avatar_type, const t_fs_filename& filename, const t_fs_path& must_be = {}) {
    const t_fs_path& path = avatar_path.get_fs_path_for_avatar(peer_id, avatar_type, filename);

    if (path != must_be) {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_get_fs_path_for_photo(const i_photo_fs_path& photo_path, const t_peer_id peer_id, const t_fs_filename& filename, const t_fs_path& must_be) {
    const t_fs_path& path = photo_path.get_fs_path_for_photo(peer_id, filename);

    if (path != must_be) {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_get_fs_path_for_stiker(const i_path_stiker& photo_path, const t_fs_filename& filename, const t_fs_path& must_be) {
    const t_fs_path& path = photo_path.get_fs_path_for_stiker(filename);

    if (path != must_be) {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_fs_common_paths() {
    const t_peer_id self_id { 1000 };
    const t_fs_common_paths& path = make_common_path("/messenger/", self_id);

    const t_peer_id peer_id { 9999 };

    test_get_fs_path_for_avatar(path, peer_id, t_avatar_type_id::t_default_avatar, "avatar.jpg", "/messenger/1000/9999/avatars/default/avatar.jpg");
    test_get_fs_path_for_avatar(path, peer_id, t_avatar_type_id::t_squared_avatar, "avatar.jpg", "/messenger/1000/9999/avatars/squared/avatar.jpg");
    test_get_fs_path_for_photo(path, peer_id, "photo.jpg", "/messenger/1000/9999/photos/photo.jpg");
    test_get_fs_path_for_stiker(path, "stiker.jpg", "/messenger/stikers/stiker.jpg");
}

