#ifndef I_UI_IMAGE_PATH_MAKER_H
#define I_UI_IMAGE_PATH_MAKER_H

#include "../t_defines.h"


class i_ui_mage_path_maker
{
public:
    virtual ~i_ui_mage_path_maker() = 0;
    
    virtual t_ui_path operator()(const t_image_type_id image_type, const t_image_id image_id) const = 0;
};

#endif // I_UI_IMAGE_PATH_MAKER_H
