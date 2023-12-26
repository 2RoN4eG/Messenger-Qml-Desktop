#ifndef T_VALUE_H
#define T_VALUE_H

#include <limits>
#include <string>

template <typename t_value>
class t_value_holder
{
public:
    using t_value_type = t_value;

    t_value_holder(t_value value = {})
        : _value { value }
    {
    }

    t_value_holder(const t_value_holder<t_value>& other) = default;
    t_value_holder<t_value>& operator=(const t_value_holder<t_value>& other) = default;

    t_value_holder(t_value_holder<t_value>&& other) = default;
    t_value_holder<t_value>& operator=(t_value_holder<t_value>&& other) = default;

    std::string to_string() const {
        return std::to_string(_value);
    }

    const t_value value() const {
        return _value;
    }

    static t_value_holder<t_value> none() {
        return std::numeric_limits<t_value>::max();
    }

protected:
    friend
        bool operator==(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
            return lhs._value == rhs._value;
        }

    friend
        bool operator<(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
            return lhs._value < rhs._value;
        }

    friend
        bool operator>(const t_value_holder<t_value>& lhs, const t_value_holder<t_value>& rhs) {
            return lhs._value > rhs._value;
        }

    friend
        std::ostream& operator<<(std::ostream& stream, const t_value_holder<t_value>& holder) {
            stream << holder.value();
            return stream;
        }

    friend
        std::filesystem::path operator/(const std::filesystem::path& path, const t_value_holder<t_value>& holder) {
            return path / holder.to_string();;
        }

    t_value _value {};
};

template <typename t_value>
class t_value_generator
{
public:
    t_value_generator()
        : _value {}
    {
    }

    const t_value_holder<t_value> get_value_and_generate_next() {
        return _value ++;
    }

    const t_value_holder<t_value> get_value_and_generate_previous() {
        return _value --;
    }

protected:
    t_value _value {};
};

#endif // T_VALUE_H
