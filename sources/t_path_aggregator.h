#ifndef T_PATH_H
#define T_PATH_H

#include "t_defines.h"


// interface section

class i_self_path_and_peer_path
{
public:
    virtual t_fs_path get_fs_path_for_self() const = 0;

    virtual t_fs_path get_fs_path_for_peer(const t_peer_id peer) const = 0;
};

class i_avatar_path {
public:
    virtual t_fs_path get_fs_path_for_avatar(const t_peer_id peer) const = 0;
    
    virtual t_fs_path get_fs_path_for_avatar(const t_peer_id peer, const t_avatar_types avatar_type) const = 0;
    
    virtual t_fs_path get_fs_path_for_avatar(const t_peer_id peer, const t_avatar_types avatar_type, const t_fs_filename& filename) const = 0;
};

class i_photo_path {
public:
    virtual t_fs_path get_fs_path_for_photo(const t_peer_id peer) const = 0;

    virtual t_fs_path get_fs_path_for_photo(const t_peer_id peer, const t_fs_filename& filename) const = 0;
    
    [[maybe_unused]] virtual t_fs_path get_fs_path_for_photo(const t_peer_id peer, const t_photo_bundle& photo_bundle, const t_fs_filename& filename) const = 0;
};

class [[maybe_unused]] i_stiker_path {
public:
    virtual t_fs_path get_fs_path_for_stiker(const t_fs_filename& filename) const = 0;
};

class [[maybe_unused]] i_database_path {
public:
    virtual t_fs_path get_fs_path_for_database(const t_fs_filename& filename) const = 0;
};

// conversation will be implemented as file with json string with stored messages
class [[maybe_unused]] i_conversation_path {
public:
    virtual t_fs_path get_fs_path_for_conversation(const t_peer_id peer) const = 0;
};


// class (interface's implementation) section

class t_common_paths
    : public i_self_path_and_peer_path
    , public i_avatar_path
    , public i_photo_path
    , public i_stiker_path
{
public:
    t_common_paths(const t_fs_path& root, const t_peer_id& self);


    // (i_self_and_peer's implementation)

    t_fs_path get_fs_path_for_self() const override;

    t_fs_path get_fs_path_for_peer(const t_peer_id peer) const override;


    // avatar section (i_avatar_path's implementation)

    // t_extra is one of { default, squared }
    // /root/self_peer/peer/avatars/default/{ list-of-default-avatars-or-single-avatar }
    // /root/self_peer/peer/avatars/squared/{ list-of-squared-avatars-or-single-avatar }

    t_fs_path get_fs_path_for_avatar(const t_peer_id peer) const override;
    
    t_fs_path get_fs_path_for_avatar(const t_peer_id peer, const t_avatar_types avatar_type) const override;
    
    t_fs_path get_fs_path_for_avatar(const t_peer_id peer, const t_avatar_types avatar_type, const t_fs_filename& filename) const override;


    // photo section (i_photo_path's implementation)

    // /root/self_peer/peer/photos/{ list-of-photos-or-single-photo }

    t_fs_path get_fs_path_for_photo(const t_peer_id peer) const override;

    t_fs_path get_fs_path_for_photo(const t_peer_id peer, const t_fs_filename& filename) const override;
    
    t_fs_path get_fs_path_for_photo(const t_peer_id peer, const t_photo_bundle& photo_bundle, const t_fs_filename& filename) const override;


    // stiker section (i_stiker_path's implementation)

    // /root/stickers/{ list-of-stikers }

    t_fs_path get_fs_path_for_stiker(const t_fs_filename& filename) const override;

protected:
    const t_fs_path& _root { "/" };

    const t_peer_id& _self;
};


// make section (fabric methods section)

t_common_paths make_common_path(const t_fs_path& root, const t_peer_id& self);


//

class i_path_maker {
public:
    virtual ~i_path_maker() = default;

    virtual t_fs_path operator()(const t_peer_id peer,
                                 const t_fs_filename& filename) const = 0;
};

class t_make_avatar_path : public i_path_maker {
public:
    t_make_avatar_path(const i_avatar_path& path, const t_avatar_types avatar_type) : _path { path }, _type { avatar_type } { }
    ~t_make_avatar_path() = default;

    t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const override { return _path.get_fs_path_for_avatar(peer, _type, filename); }

private:
    const i_avatar_path& _path;
    
    const t_avatar_types _type;
};

class t_make_photo_path : public i_path_maker {
public:
    t_make_photo_path(const i_photo_path& path) : _path { path } { }
    ~t_make_photo_path() = default;

    t_fs_path operator()(const t_peer_id peer, const t_fs_filename& filename) const override { return _path.get_fs_path_for_photo(peer, filename); }

private:
    const i_photo_path& _path;
};


// test section (to avoid wasting time is located here)

void test_path();

#endif // T_PATH_H
