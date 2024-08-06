#pragma once

#include <types/types.h>

#include <stack>
#include <string>

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

    inline bool is_eof() const;
    inline Char get_current() const;
    inline void move_next();
    inline bool is_equal(Char c) const;
    inline bool in_bounds(Char min, Char max) const;

    inline void push_save();
    inline void pop_save();
    inline void load_save(bool pop = true);
    inline size_t get_save_length();
    inline std::string_view get_save_string();

    bool require(Char c);
    bool require(std::string_view str);

    bool get_whitespace();
    bool get_digit(Nat8 &out_digit);
    bool get_hex_digit(Nat8 &out_digit);

  private:
    std::string_view data;
    size_t current_index;
    std::stack<size_t> saved_indices;
};
}  // namespace Parsing

namespace Parsing {
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

inline void Parser::load_save(bool pop)
{
    size_t save_index = this->saved_indices.top();
    this->current_index = save_index;
    if (pop) {
        this->saved_indices.pop();
    }
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

inline bool Parser::is_equal(Char c) const
{
    return get_current() == c;
}

inline bool Parser::in_bounds(Char min, Char max) const
{
    return get_current() >= min && get_current() <= max;
}
}  // namespace Parsing