#include "parser.h"
namespace CppParser {
inline Parser::Parser(std::string_view data) : data(data), current_index(0) {}

inline bool Parser::is_eof() const
{
    return this->current_index >= data.size();
}

inline Char Parser::get_current() const
{
    return this->data[this->current_index];
}

inline void Parser::move_next()
{
    this->current_index++;
}

inline void Parser::push_save()
{
    this->saved_indices.push(this->current_index);
}

inline void Parser::pop_save()
{
    this->saved_indices.pop();
}

inline void Parser::load_save()
{
    size_t save_index = this->saved_indices.top();
    this->saved_indices.pop();
    this->current_index = save_index;
}

inline size_t Parser::get_save_length()
{
    return this->current_index - saved_indices.top();
}

inline std::string_view Parser::get_save_string()
{
    size_t save_index = saved_indices.top();
    return std::string_view(&this->data[save_index], get_save_length());
}

inline bool Parser::require(Char c)
{
    if (is_eof() || get_current() != c) {
        return false;
    }
    move_next();
    return true;
}

inline bool Parser::require(std::string_view str)
{
    for (Char c : str) {
        if (!require(c)) {
            return false;
        }
    }
    return true;
}

inline bool Parser::get_whitespace()
{
    while (!is_eof() && (get_current() == ' ' || get_current() == '\t')) {
        move_next();
    }
    return true;
}

bool Parser::get_digit(Nat8 &out_digit)
{
    if (is_eof() || !in_bounds('0', '9')) {
        return false;
    }
    out_digit = get_current() - '0';
    move_next();
    return true;
}

bool Parser::get_hex_digit(Nat8 &out_digit)
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

inline bool Parser::is_equal(Char c)
{
    return get_current() == c;
}

inline bool Parser::in_bounds(Char min, Char max)
{
    return get_current() >= min && get_current() <= max;
}
}  // namespace CppParser