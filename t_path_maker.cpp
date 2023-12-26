#include "t_path_maker.h"

#include <iostream>

//
//
//

namespace {
    inline t_path make_self_path(const t_path& root, const t_peer& self) {
        return root / self.to_string();
    }
}

//
// class section
//

t_path_maker::t_path_maker(const t_path& root, const t_peer& self)
    : _root { root }
    , _self { self }
{
}

//

t_path t_path_maker::make_path_for_self() const {
    return ::make_self_path(_root, _self);
}

t_path t_path_maker::make_path_for_peer(const t_peer peer) const {
    return make_path_for_self() / peer.to_string();
}

//

t_path t_path_maker::make_path_for_avatar(const t_peer peer) const {
    return make_path_for_peer(peer) / "avatars";
}

t_path t_path_maker::make_path_for_avatar(const t_peer peer, const t_avatar_type avatar_type) const {
    return make_path_for_avatar(peer) / to_string(avatar_type);
}

t_path t_path_maker::make_path_for_avatar(const t_peer peer, const t_avatar_type avatar_type, const t_filename& filename) const {
    return make_path_for_avatar(peer, avatar_type) / filename;
}

//

t_path t_path_maker::make_path_for_photo(const t_peer peer) const {
    return make_path_for_peer(peer) / "photos";
}

t_path t_path_maker::make_path_for_photo(const t_peer peer, const t_filename& filename) const {
    return make_path_for_photo(peer) / filename;
}

//

t_path t_path_maker::make_path_for_stiker(const t_filename& filename) const {
    return _root / "stikers" / filename;
}

// make section (fabric methods section)

t_path_maker make_path_maker(const t_path& root, const t_peer& self) {
    return t_path_maker { root, self };
}

// test section (to avoid wasting time is located here)

void test_path_maker__make_path_for_avatar(const i_avatar_path_maker& avatar_path_maker, const t_peer peer, const t_avatar_type avatar_type, const t_filename& filename, const t_path& must_be = {}) {
    const t_path& path = avatar_path_maker.make_path_for_avatar(peer, avatar_type, filename);

    if (path != must_be) {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_path_maker__make_path_for_photo(const i_photo_path_maker& photo_path_maker, const t_peer peer, const t_filename& filename, const t_path& must_be) {
    const t_path& path = photo_path_maker.make_path_for_photo(peer, filename);

    if (path != must_be) {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_path_maker__make_path_for_stiker(const i_stiker_path_maker& photo_path_maker, const t_filename& filename, const t_path& must_be) {
    const t_path& path = photo_path_maker.make_path_for_stiker(filename);

    if (path != must_be) {
        throw std::runtime_error { "path " + path.string() + " does not equal with must_be path " + must_be.string() };
    }
}

void test_path_maker() {
    t_peer self { 1000 };
    const t_path_maker& path_maker = make_path_maker("/messenger/", self);

    const t_peer peer { 9999 };

    test_path_maker__make_path_for_avatar(path_maker, peer, t_avatar_type::t_default, "avatar.jpg", "/messenger/1000/9999/avatars/default/avatar.jpg");
    test_path_maker__make_path_for_avatar(path_maker, peer, t_avatar_type::t_squared, "avatar.jpg", "/messenger/1000/9999/avatars/squared/avatar.jpg");

    test_path_maker__make_path_for_photo(path_maker, peer, "photo.jpg", "/messenger/1000/9999/photos/photo.jpg");

    test_path_maker__make_path_for_stiker(path_maker, "stiker.jpg", "/messenger/stikers/stiker.jpg");
}
