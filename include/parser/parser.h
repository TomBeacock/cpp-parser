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

    inline void new_save();
    inline void remove_save();
    inline void load_save();
    inline size_t save_length();

    inline bool require(Char c);
    inline bool require(std::string_view str);

    inline bool get_whitespace();
    inline bool get_digit(Nat8 &out_digit);
    inline bool get_hex_digit(Nat8 &out_digit);

    inline bool in_bounds(Char min, Char max);

  private:
    std::string_view data;
    size_t current_index;
    std::stack<size_t> saved_indices;
};
}  // namespace CppParser

#include "parser.inl"