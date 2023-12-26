#ifndef T_PATH_MAKER_H
#define T_PATH_MAKER_H

#include "t_defines.h"

// interface section

class i_self_and_peer_maker {
public:
    virtual t_path make_path_for_self() const = 0;

    virtual t_path make_path_for_peer(const t_peer peer) const = 0;
};

class i_avatar_path_maker {
public:
    virtual t_path make_path_for_avatar(const t_peer peer) const = 0;

    virtual t_path make_path_for_avatar(const t_peer peer, const t_avatar_type avatar_type) const = 0;

    virtual t_path make_path_for_avatar(const t_peer peer, const t_avatar_type avatar_type, const t_filename& filename) const = 0;
};

class i_photo_path_maker {
public:
    virtual t_path make_path_for_photo(const t_peer peer) const = 0;

    virtual t_path make_path_for_photo(const t_peer peer, const t_filename& filename) const = 0;
};

class i_stiker_path_maker {
public:
    virtual t_path make_path_for_stiker(const t_filename& filename) const = 0;
};

// complex interface section

class i_path_maker : public i_self_and_peer_maker, public i_avatar_path_maker, public i_photo_path_maker, public i_stiker_path_maker {
};

// class (interface's implementation) section

// alternative names are t_path_manipulator, i_image_path_maker
class t_path_maker : public i_path_maker
{
public:
    t_path_maker(const t_path& root, const t_peer& self);

    // (i_self_and_peer_maker's implementation)

    t_path make_path_for_self() const override;

    t_path make_path_for_peer(const t_peer peer) const override;

    // avatar section (i_avatar_path_maker's implementation)

    // t_extra is one of { default, squared }
    // /root/self_peer/peer/avatars/default/{list-of-default-avatars-or-single-avatar}
    // /root/self_peer/peer/avatars/squared/{list-of-squared-avatars-or-single-avatar}

    t_path make_path_for_avatar(const t_peer peer) const override;

    t_path make_path_for_avatar(const t_peer peer, const t_avatar_type avatar_type) const override;

    t_path make_path_for_avatar(const t_peer peer, const t_avatar_type avatar_type, const t_filename& filename) const override;

    // photo section (i_photo_path_maker's implementation)

    // /root/self_peer/peer/photos/{list-of-photos-or-single-photo}

    t_path make_path_for_photo(const t_peer peer) const override;

    t_path make_path_for_photo(const t_peer peer, const t_filename& filename) const override;

    // stiker section (i_stiker_path_maker's implementation)

    // /root/stickers/{list-of-stikers}

    t_path make_path_for_stiker(const t_filename& filename) const override;

    // database section

protected:
    const t_path& _root { "/" };

    const t_peer& _self;
};

// make section (fabric methods section)

t_path_maker make_path_maker(const t_path& root, const t_peer& self);

//

class i_path_holder {
public:
    virtual t_path operator()(const t_peer peer, const t_filename& filename) const = 0;
};

class t_avatar_path_holder : public i_path_holder {
public:
    t_avatar_path_holder(const i_path_maker& image_path_maker, const t_avatar_type avatar_type) : _image_path_maker { image_path_maker }, _avatar_type { avatar_type } { }

    t_path operator()(const t_peer peer, const t_filename& filename) const override { return _image_path_maker.make_path_for_avatar(peer, _avatar_type, filename); }

private:
    const i_path_maker& _image_path_maker;

    const t_avatar_type _avatar_type;
};

class t_photo_path_holder : public i_path_holder {
public:
    t_photo_path_holder(const i_photo_path_maker& photo_path_maker) : _photo_path_maker { photo_path_maker } { }

    t_path operator()(const t_peer peer, const t_filename& filename) const override { return _photo_path_maker.make_path_for_photo(peer, filename); }

private:
    const i_photo_path_maker& _photo_path_maker;
};

// test section (to avoid wasting time is located here)

void test_path_maker();

#endif // T_PATH_MAKER_H
