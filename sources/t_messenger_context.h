#ifndef T_MESSENGER_CONTEXT_H
#define T_MESSENGER_CONTEXT_H

#include <string>


class t_image_info_storage;

using t_ui_avatar = std::string;

// alternative name is t_core_context
class t_messenger_context
{
public:
    t_messenger_context(t_image_info_storage& image_info_storage);

    t_ui_avatar get_avatar() {

    }

private:
    t_image_info_storage& _image_info_storage;
};

#endif // T_MESSENGER_CONTEXT_H
