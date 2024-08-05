#include "parser.h"
namespace CppParser {
template <typename T, typename U>
inline Parser<T, U>::Parser(std::string_view data)
    : data(data),
      current_index(0)
{}

template <typename T, typename U>
inline bool Parser<T, U>::is_eof() const
{
    return this->current_index >= data.size();
}

template <typename T, typename U>
inline Char Parser<T, U>::get_current() const
{
    return this->data[this->current_index];
}

template <typename T, typename U>
inline void Parser<T, U>::move_next()
{
    this->current_index++;
}

template <typename T, typename U>
inline void Parser<T, U>::new_save()
{
    this->saved_indices.push(this->current_index);
}

template <typename T, typename U>
inline void Parser<T, U>::remove_save()
{
    this->saved_indices.pop();
}

template <typename T, typename U>
inline void Parser<T, U>::load_save()
{
    size_t save_index = this->saved_indices.top();
    this->saved_indices.pop();
    this->current_index = save_index;
}

template <typename T, typename U>
inline size_t Parser<T, U>::get_save_length()
{
    return this->current_index - saved_indices.top();
}

template <typename T, typename U>
inline std::string_view Parser<T, U>::get_save_string()
{
    size_t save_index = saved_indices.top();
    return std::string_view(&this->data[save_index], get_save_length());
}

template <typename T, typename U>
inline bool Parser<T, U>::require(Char c)
{
    if (is_eof() || get_current() != c) {
        return false;
    }
    move_next();
    return true;
}

template <typename T, typename U>
inline bool Parser<T, U>::require(std::string_view str)
{
    for (Char c : str) {
        if (!require(c)) {
            return false;
        }
    }
    return true;
}

template <typename T, typename U>
inline bool Parser<T, U>::get_whitespace()
{
    while (!is_eof() && (get_current() == ' ' || get_current() == '\t')) {
        move_next();
    }
    return true;
}

template <typename T, typename U>
bool Parser<T, U>::get_digit(Nat8 &out_digit)
{
    if (is_eof() || !in_bounds('0', '9')) {
        return false;
    }
    out_digit = get_current() - '0';
    move_next();
    return true;
}

template <typename T, typename U>
bool Parser<T, U>::get_hex_digit(Nat8 &out_digit)
{
    if (is_eof()) {
        return false;
    }
    if (in_bounds('0', '9')) {
        out_digit = get_current() - '0';
    } else if (in_bounds('a', 'f')) {
        out_digit = get_current() - 'a' + 10;
    } else if (in_bounds('A', 'F')) {
        out_digit = get_current() - 'A' + 10;
    } else {
        return false;
    }
    move_next();
    return true;
}

template <typename T, typename U>
inline bool Parser<T, U>::is_equal(Char c)
{
    return get_current() == c;
}

template <typename T, typename U>
inline bool Parser<T, U>::in_bounds(Char min, Char max)
{
    return get_current() >= min && get_current() <= max;
}
}  // namespace CppParser