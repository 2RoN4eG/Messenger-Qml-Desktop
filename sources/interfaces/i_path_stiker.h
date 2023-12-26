#ifndef I_PATH_STIKER_H
#define I_PATH_STIKER_H

#include "../t_defines.h"

class [[maybe_unused]] i_path_stiker
{
public:
    virtual ~i_path_stiker() = 0;

    virtual t_fs_path get_fs_path_for_stiker(const t_fs_filename& filename) const = 0;
};

#endif // I_PATH_STIKER_H
