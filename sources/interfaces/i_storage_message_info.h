#ifndef I_STORAGE_MESSAGE_INFO_H
#define I_STORAGE_MESSAGE_INFO_H

#include "../t_defines.h"

class i_message_info_storage
{
public:
    virtual ~i_message_info_storage() = 0;


    virtual void set_message_info(const t_message_id message_id,
                                  const t_peer_id peer_id,
                                  const t_message_text& text,
                                  const t_message_timestamp timestamp) = 0;

    virtual void set_message_info(const t_message_id message_id,
                                  const t_peer_id peer_id,
                                  const t_photo_id photo_id,
                                  const t_message_text& text,
                                  const t_message_timestamp timestamp) = 0;

    virtual t_peer_id get_message_peer_id(const t_message_id message_id) const = 0;

    virtual bool does_message_photo_exist(const t_message_id message_id) const = 0;

    virtual t_photo_id get_message_photo_id(const t_message_id message_id) const = 0;

    virtual t_message_text get_message_text(const t_message_id message_id) const = 0;

    virtual t_message_timestamp get_message_timestamp(const t_message_id message_id) const = 0;

    virtual t_message_infos& message_infos() const = 0;

    virtual const size_t size() const = 0;

    virtual const t_message_id operator[](size_t index) const = 0;
};

#endif // I_STORAGE_MESSAGE_INFO_H
