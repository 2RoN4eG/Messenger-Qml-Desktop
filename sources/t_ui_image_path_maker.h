#ifndef T_UI_IMAGE_PATH_MAKER_H
#define T_UI_IMAGE_PATH_MAKER_H

#include "t_defines.h"
#include "interfaces/i_ui_image_path_maker.h"

class t_ui_mage_path_maker : public i_ui_mage_path_maker
{
public:
    ~t_ui_mage_path_maker() override;
    
    t_ui_path operator()(const t_image_type_id image_type, const t_image_id image_id) const override;
};

#endif // T_UI_IMAGE_PATH_MAKER_H
