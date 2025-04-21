#ifndef T_PATH_H
#define T_PATH_H

#include "t_defines.h"

#include "interfaces/i_path_self_and_peer.h"
#include "interfaces/i_avatar_fs_path.hpp"
#include "interfaces/i_photo_path.hpp"
#include "interfaces/i_stiker_fs_path.hpp"

#include <iostream>

// class (interface's implementation) section

class t_compound_fs_path_maker
    : public i_peer_fs_path
    , public i_avatar_fs_path
    , public i_photo_fs_path
    , public i_stiker_fs_path
{
public:
    t_compound_fs_path_maker(const t_fs_path& root, const t_peer_id& self);
    t_compound_fs_path_maker() = default;


    // self and peer's implementation

    const t_fs_path get_self_fs_path() const override;

    const t_fs_path get_peer_fs_path(const t_peer_id peer) const override;


    // avatar section (i_avatar_fs_path's implementation)

    // /<root>/<self_peer_id>/<peer_id>/avatars/<t_avatar_type::default>/{ list-of-default-avatars-or-single-avatar }
    // /<root>/<self_peer_id>/<peer_id>/avatars/<t_avatar_type::squared>/{ list-of-squared-avatars-or-single-avatar }
    // /<root>/<self_peer_id>/<peer_id>/avatars/<t_avatar_type::rounded>/{ list-of-squared-avatars-or-single-avatar }

    const t_fs_path get_avatar_fs_path(const t_peer_id peer) const override;

    const t_fs_path get_avatar_fs_path(const t_peer_id peer, const t_avatar_type_id avatar_type) const override;

    const t_fs_path get_avatar_fs_path(const t_peer_id peer, const t_avatar_type_id avatar_type, const t_fs_filename& filename) const override;


    // photo section (i_photo_path's implementation)

    // /<root>/<self_peer_id>/<peer_id>/photos/{ list-of-photos-or-single-photo }
    // /<root>/<self_peer_id>/<peer_id>/photos/<bundle_id>/{ list-of-photos-or-single-photo }

    const t_fs_path get_photo_fs_path(const t_peer_id peer) const override;

    const t_fs_path get_photo_fs_path(const t_peer_id peer, const t_fs_filename& filename) const override;

    const t_fs_path get_photo_fs_path(const t_peer_id peer, const t_photo_bundle_id& bundle_id, const t_fs_filename& filename) const override;


    // stiker section (i_stiker_fs_path's implementation)

    // /<root>/stickers/{ list-of-stikers }

    const t_fs_path get_fs_path_for_stiker(const t_fs_filename& filename) const override;

protected:
    const t_fs_path _root;

    const t_peer_id _self_peer_id;
};


// make section (fabric methods section)

const t_compound_fs_path_maker make_compaund_fs_path_maker(const t_fs_path& root, const t_peer_id& self);


class i_file_fs_path_maker
{
public:
    virtual ~i_file_fs_path_maker() = 0;

    virtual const t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const = 0;
};


class t_avatar_fs_path_maker : public i_file_fs_path_maker
{
public:
    t_avatar_fs_path_maker(const i_avatar_fs_path& path, const t_avatar_type_id avatar_type)
        : _path { path }
        , _type { avatar_type }
    {
    }
    ~t_avatar_fs_path_maker() = default;

    const t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const override
    {
        const t_fs_path fs_path = _path.get_avatar_fs_path(peer, _type, filename);

        std::cout << "fs path is " << fs_path << std::endl;

        return fs_path;
    }

private:
    const i_avatar_fs_path& _path;

    const t_avatar_type_id _type;
};


class t_photo_fs_path_maker : public i_file_fs_path_maker
{
public:
    t_photo_fs_path_maker(const i_photo_fs_path& path)
        : _path { path }
    {
    }
    ~t_photo_fs_path_maker() = default;

    const t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const override
    {
        const t_fs_path fs_path = _path.get_photo_fs_path(peer, filename);

        std::cout << "fs path is " << fs_path << std::endl;

        return fs_path;
    }

private:
    const i_photo_fs_path& _path;
};


class t_file_fs_path_maker : public i_file_fs_path_maker
{
public:
    t_file_fs_path_maker() = default;
    ~t_file_fs_path_maker() = default;

    const t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const override
    {
        const t_fs_path fs_path {};

        std::cout << "fs path is " << fs_path << std::endl;

        return fs_path;
    }
};


// test section (to avoid wasting time is located here)

void test_compound_fs_path_maker();

#endif // T_PATH_H
