#pragma once

#include <types/types.h>

#include <stack>
#include <string>
#include <variant>

namespace Parsing {
/**
 * @brief Base class for creating a top-down parser.
 */
class Parser {
  public:
    Parser(Parser &parser) = delete;
    Parser(Parser &&parser) = delete;

    Parser &operator=(const Parser &parser) = delete;
    Parser &operator=(const Parser &&parser) = delete;

  protected:
    Parser(std::string_view data);

    inline Char get_current() const;
    inline Bool is_eof() const;
    inline Bool is_equal(Char c) const;
    inline Bool in_bounds(Char min, Char max) const;

    inline void move_next();
    inline Size get_remaining() const;

    inline void push_save();
    inline void pop_save();
    inline void load_save(Bool pop = true);
    inline Size get_save_length();
    inline std::string_view get_save_string();

    Bool require(Char c);
    Bool require(std::string_view str);

    Bool get_whitespace();
    Bool get_digit(Nat8 &out_digit);
    Bool get_hex_digit(Nat8 &out_digit);
    Bool get_int(Int &out_int);
    Bool get_nat(Nat &out_nat);
    Bool get_float(Float &out_float);
    Bool get_number(std::variant<Int, Float> &out_number);

  private:
    std::string_view data;
    Size current_index;
    std::stack<Size> saved_indices;
};
}  // namespace Parsing

namespace Parsing {
inline Parser::Parser(std::string_view data) : data(data), current_index(0) {}

inline Char Parser::get_current() const
{
    return this->data[this->current_index];
}

inline Bool Parser::is_eof() const
{
    return this->current_index >= data.size();
}

inline Bool Parser::is_equal(Char c) const
{
    return get_current() == c;
}

inline Bool Parser::in_bounds(Char min, Char max) const
{
    return get_current() >= min && get_current() <= max;
}

inline void Parser::move_next()
{
    this->current_index++;
}

inline Size Parser::get_remaining() const
{
    return this->data.size() - this->current_index;
}

inline void Parser::push_save()
{
    this->saved_indices.push(this->current_index);
}

inline void Parser::pop_save()
{
    this->saved_indices.pop();
}

inline void Parser::load_save(Bool pop)
{
    Size save_index = this->saved_indices.top();
    this->current_index = save_index;
    if (pop) {
        this->saved_indices.pop();
    }
}

inline Size Parser::get_save_length()
{
    return this->current_index - saved_indices.top();
}

inline std::string_view Parser::get_save_string()
{
    Size save_index = saved_indices.top();
    return std::string_view(&this->data[save_index], get_save_length());
}
}  // namespace Parsing