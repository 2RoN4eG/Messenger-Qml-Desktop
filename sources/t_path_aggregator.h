#ifndef T_PATH_H
#define T_PATH_H

#include "t_defines.h"

#include "interfaces/i_path_self_and_peer.h"
#include "interfaces/i_avatar_fs_path.hpp"
#include "interfaces/i_photo_path.hpp"
#include "interfaces/i_path_stiker.h"

#include <iostream>

// class (interface's implementation) section

class t_common_fs_path_maker
    : public i_path_self_path_and_peer
    , public i_avatar_fs_path
    , public i_photo_fs_path
    , public i_path_stiker
{
public:
    t_common_fs_path_maker(const t_fs_path& root, const t_peer_id& self);
    t_common_fs_path_maker() = default;

    // (i_self_and_peer's implementation)

    t_fs_path get_self_fs_path() const override;

    t_fs_path get_peer_fs_path(const t_peer_id peer) const override;

    // avatar section (i_avatar_fs_path's implementation)

    // t_extra (t_avatar_type) is one of { default, squared, rounded }

    // /root/<self_peer_id>/<peer_id>/avatars/<t_avatar_type::default>/{ list-of-default-avatars-or-single-avatar }
    // /root/<self_peer_id>/<peer_id>/avatars/<t_avatar_type::squared>/{ list-of-squared-avatars-or-single-avatar }

    t_fs_path get_avatar_fs_path(const t_peer_id peer) const override;

    t_fs_path get_avatar_fs_path(const t_peer_id peer, const t_avatar_type_id avatar_type) const override;

    t_fs_path get_avatar_fs_path(const t_peer_id peer, const t_avatar_type_id avatar_type, const t_fs_filename& filename) const override;

    // photo section (i_photo_path's implementation)

    // /root/<self_peer_id>/<peer_id>/photos/{ list-of-photos-or-single-photo }
    // /root/<self_peer_id>/<peer_id>/photos/<bundle_id>/{ list-of-photos-or-single-photo }

    t_fs_path get_photo_fs_path(const t_peer_id peer) const override;

    t_fs_path get_photo_fs_path(const t_peer_id peer, const t_fs_filename& filename) const override;

    t_fs_path get_photo_fs_path(const t_peer_id peer, const t_photo_bundle_id& bundle_id, const t_fs_filename& filename) const override;

    // stiker section (i_stiker_path's implementation)

    // /root/stickers/{ list-of-stikers }

    t_fs_path get_fs_path_for_stiker(const t_fs_filename& filename) const override;

protected:
    t_fs_path _root;

    t_peer_id _self_peer_id;
};

// make section (fabric methods section)

t_common_fs_path_maker make_root_path(const t_fs_path& root, const t_peer_id& self);


class i_image_fs_path_maker
{
public:
    virtual ~i_image_fs_path_maker() = 0;

    virtual t_fs_path operator()(const t_peer_id peer,
                                 const t_fs_filename& filename) const = 0;
};


class t_avatar_fs_path_maker : public i_image_fs_path_maker
{
public:
    t_avatar_fs_path_maker(const i_avatar_fs_path& path, const t_avatar_type_id avatar_type)
        : _path { path }
        , _type { avatar_type }
    {
    }
    ~t_avatar_fs_path_maker() = default;

    t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const override
    {
        t_fs_path fs_path = _path.get_avatar_fs_path(peer, _type, filename);

        std::cout << "fs path is " << fs_path << std::endl;

        return fs_path;
    }

private:
    const i_avatar_fs_path& _path;

    const t_avatar_type_id _type;
};

class t_photo_fs_path_maker : public i_image_fs_path_maker
{
public:
    t_photo_fs_path_maker(const i_photo_fs_path& path)
        : _path { path }
    {
    }
    ~t_photo_fs_path_maker() = default;

    t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const override
    {
        t_fs_path fs_path = _path.get_photo_fs_path(peer, filename);

        std::cout << "fs path is " << fs_path << std::endl;

        return fs_path;
    }

private:
    const i_photo_fs_path& _path;
};

// test section (to avoid wasting time is located here)

void test_common_fs_path_maker();

#endif // T_PATH_H
