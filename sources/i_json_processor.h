#ifndef I_JSON_PROCESSOR_H
#define I_JSON_PROCESSOR_H

#include <string>


class i_json_processor
{
public:
    virtual ~i_json_processor() = 0;

    virtual void operator()(const std::string_view json) const = 0;
};

#endif // I_JSON_PROCESSOR_H
