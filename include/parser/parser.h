#pragma once

#include <types/types.h>

#include <stack>
#include <string>

namespace CppParser {
/**
 * @brief Base class for creating a parser.
 * @tparam T The resulting type after parsing.
 * @tparam U The success/failure response type.
 */
template <typename T, typename U = bool>
class Parser {
  public:
    Parser(Parser &parser) = delete;
    Parser(Parser &&parser) = delete;

    Parser &operator=(const Parser &parser) = delete;
    Parser &operator=(const Parser &&parser) = delete;

    virtual U parse(T &out) = 0;

  protected:
    Parser(std::string_view data);

    inline bool is_eof() const;
    inline Char get_current() const;
    inline void move_next();

    inline void push_save();
    inline void pop_save();
    inline void load_save();
    inline size_t get_save_length();
    inline std::string_view get_save_string();

    inline bool require(Char c);
    inline bool require(std::string_view str);

    inline bool get_whitespace();
    inline bool get_digit(Nat8 &out_digit);
    inline bool get_hex_digit(Nat8 &out_digit);

    inline bool is_equal(Char c);
    inline bool in_bounds(Char min, Char max);

  private:
    std::string_view data;
    size_t current_index;
    std::stack<size_t> saved_indices;
};
}  // namespace CppParser

#include "parser.inl"