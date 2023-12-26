#include "t_ui_image_path_maker.h"

inline t_ui_string to_ui_string(const t_image_type_id image_type_id)
{
    switch (image_type_id)
    {
    case t_image_type_id::t_default_avatar_image:
        return "image://default/";
    case t_image_type_id::t_squared_avatar_image:
        return "image://squared/";
    case t_image_type_id::t_photo_image:
        return "image://photos/";
    case t_image_type_id::t_stiker_image:
        return "image://stiker/";
    default:
        break;
    }

    throw std::runtime_error { "t_image_type is undefined" };
}

t_ui_mage_path_maker::~t_ui_mage_path_maker() {}

t_ui_string t_ui_mage_path_maker::operator()(const t_image_type_id image_type, const t_image_id image_id) const
{
    return to_ui_string(image_type) + t_ui_string::number(image_id.value());
}
