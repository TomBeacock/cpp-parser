#include "parser/parser.h"

namespace Parsing {
bool Parser::require(Char c)
{
    if (is_eof() || get_current() != c) {
        return false;
    }
    move_next();
    return true;
}

bool Parser::require(std::string_view str)
{
    for (Char c : str) {
        if (!require(c)) {
            return false;
        }
    }
    return true;
}

bool Parser::get_whitespace()
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
}  // namespace Parsing