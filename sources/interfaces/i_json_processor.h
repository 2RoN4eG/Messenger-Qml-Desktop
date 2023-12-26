#ifndef I_JSON_PROCESSOR_H
#define I_JSON_PROCESSOR_H

#include <string_view>

using t_json_string_view = std::string_view;

class i_json_processor
{
public:
    virtual ~i_json_processor() = 0;

    virtual void operator()(const t_json_string_view json) const = 0;
};

#endif // I_JSON_PROCESSOR_H
