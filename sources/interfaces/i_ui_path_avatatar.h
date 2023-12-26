#ifndef I_UI_PATH_AVATATAR_H
#define I_UI_PATH_AVATATAR_H

#include "../t_defines.h"

class i_ui_path_avatatar
{
public:
    virtual ~i_ui_path_avatatar() = 0;

    virtual t_ui_path get_ui_path_for_avatar(const t_peer_id peer) const = 0;

};

#endif // I_UI_PATH_AVATATAR_H
