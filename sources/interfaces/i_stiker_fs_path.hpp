#pragma once

#include "../t_defines.h"

class [[maybe_unused]] i_stiker_fs_path
{
public:
    virtual ~i_stiker_fs_path() = 0;

    virtual const t_fs_path get_fs_path_for_stiker(const t_fs_filename& filename) const = 0;
};
