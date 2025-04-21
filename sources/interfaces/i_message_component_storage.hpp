#pragma once

#include "../t_defines.h"


class i_message_component_storage
{
public:
    virtual ~i_message_component_storage() = 0;


    virtual void set_message_component(const t_message_id message_id, const t_peer_id peer_id, const t_message_text& text, const t_message_timestamp timestamp) = 0;

    virtual void set_message_component(const t_message_id message_id, const t_peer_id peer_id, const t_photo_id photo_id, const t_message_text& text, const t_message_timestamp timestamp) = 0;


    virtual t_peer_id get_message_peer_id(const t_message_id message_id) const = 0;

    virtual bool does_message_photo_exist(const t_message_id message_id) const = 0;

    virtual bool does_message_photo_bundle_exist(const t_message_id message_id) const
    {
        return {};
    }

    virtual t_photo_id get_message_photo_id(const t_message_id message_id) const = 0;

    virtual t_photo_bundle_id get_message_photo_bundle_id(const t_message_id message_id) const
    {
        return {};
    }

    virtual t_message_text get_message_text(const t_message_id message_id) const = 0;

    virtual t_message_timestamp get_message_timestamp(const t_message_id message_id) const = 0;

    virtual t_message_components& message_components() const = 0;

    virtual const size_t size() const = 0;

    virtual const t_message_id operator[](size_t index) const = 0;
};
