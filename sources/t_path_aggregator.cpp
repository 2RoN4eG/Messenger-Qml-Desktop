#include "t_path_aggregator.h"

namespace
{
    constexpr const char* t_avatars_pathname = "avatars";
    constexpr const char* t_photos_pathname  = "photos";
    constexpr const char* t_stikers_pathname = "stikers";
}


i_file_fs_path_maker::~i_file_fs_path_maker()
{
}

//
// class section
//

t_compound_fs_path_maker::t_compound_fs_path_maker(const t_fs_path& root, const t_peer_id& self)
    : _root { root }
    , _self_peer_id { self }
{
}

//
//
//

const t_fs_path t_compound_fs_path_maker::get_self_fs_path() const
{
    return _root / _self_peer_id;
}

const t_fs_path t_compound_fs_path_maker::get_peer_fs_path(const t_peer_id peer_id) const
{
    return get_self_fs_path() / peer_id;
}

//
//
//

const t_fs_path t_compound_fs_path_maker::get_avatar_fs_path(const t_peer_id peer_id) const
{
    return get_peer_fs_path(peer_id) / t_avatars_pathname;
}

const t_fs_path t_compound_fs_path_maker::get_avatar_fs_path(const t_peer_id peer_id, const t_avatar_type_id avatar_type) const
{
    return get_avatar_fs_path(peer_id) / to_string(avatar_type);
}

const t_fs_path t_compound_fs_path_maker::get_avatar_fs_path(const t_peer_id peer_id, const t_avatar_type_id avatar_type, const t_fs_filename& filename) const
{
    return get_avatar_fs_path(peer_id, avatar_type) / filename;
}

//
//
//

const t_fs_path t_compound_fs_path_maker::get_photo_fs_path(const t_peer_id peer_id) const
{
    return get_peer_fs_path(peer_id) / t_photos_pathname;
}

const t_fs_path t_compound_fs_path_maker::get_photo_fs_path(const t_peer_id peer_id, const t_fs_filename& filename) const
{
    return get_photo_fs_path(peer_id) / filename;
}

const t_fs_path t_compound_fs_path_maker::get_photo_fs_path(const t_peer_id peer_id, const t_photo_bundle_id& bundle_id, const t_fs_filename& filename) const
{
    return get_photo_fs_path(peer_id) / bundle_id / filename;
}

//
//
//

const t_fs_path t_compound_fs_path_maker::get_fs_path_for_stiker(const t_fs_filename& filename) const
{
    return _root / t_stikers_pathname / filename;
}

//
// make section (fabric methods section)
//

const t_compound_fs_path_maker make_compaund_fs_path_maker(const t_fs_path& root, const t_peer_id& self)
{
    return t_compound_fs_path_maker { root, self };
}

// test section (to avoid wasting time is located here)

void test_get_avatar_fs_path(const i_avatar_fs_path& avatar_path, const t_peer_id peer_id, const t_avatar_type_id avatar_type, const t_fs_filename& filename, const t_fs_path& must_be = {})
{
    const t_fs_path& path = avatar_path.get_avatar_fs_path(peer_id, avatar_type, filename);
    if (path != must_be)
    {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_get_photo_fs_path(const i_photo_fs_path& photo_path, const t_peer_id peer_id, const t_fs_filename& filename, const t_fs_path& must_be)
{
    const t_fs_path& path = photo_path.get_photo_fs_path(peer_id, filename);
    if (path != must_be)
    {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_get_fs_path_for_stiker(const i_stiker_fs_path& photo_path, const t_fs_filename& filename, const t_fs_path& must_be)
{
    const t_fs_path& path = photo_path.get_fs_path_for_stiker(filename);
    if (path != must_be)
    {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_compound_fs_path_maker()
{
    const t_peer_id self_id { 1000 };
    const t_compound_fs_path_maker& path = make_compaund_fs_path_maker("/messenger/", self_id);

    const t_peer_id peer_id { 9999 };

    test_get_avatar_fs_path(path, peer_id, t_avatar_type_id::t_default_avatar, "avatar.jpg", "/messenger/1000/9999/avatars/default/avatar.jpg");

    test_get_avatar_fs_path(path, peer_id, t_avatar_type_id::t_squared_avatar, "avatar.jpg", "/messenger/1000/9999/avatars/squared/avatar.jpg");

    test_get_photo_fs_path(path, peer_id, "photo.jpg", "/messenger/1000/9999/photos/photo.jpg");

    test_get_fs_path_for_stiker(path, "stiker.jpg", "/messenger/stikers/stiker.jpg");
}

