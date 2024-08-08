#include "parser/parser.h"

namespace Parsing {
Bool Parser::require(Char c)
{
    if (is_eof() || get_current() != c) {
        return false;
    }
    move_next();
    return true;
}

Bool Parser::require(std::string_view str)
{
    for (Char c : str) {
        if (!require(c)) {
            return false;
        }
    }
    return true;
}

Bool Parser::get_whitespace()
{
    while (!is_eof() && (get_current() == ' ' || get_current() == '\t')) {
        move_next();
    }
    return true;
}

Bool Parser::get_digit(Nat8 &out_digit)
{
    if (is_eof() || !in_bounds('0', '9')) {
        return false;
    }
    out_digit = get_current() - '0';
    move_next();
    return true;
}

Bool Parser::get_hex_digit(Nat8 &out_digit)
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

Bool Parser::get_int(Int &out_int)
{
    push_save();
    Bool neg = require('-');
    Nat8 digit;
    if (!get_digit(digit)) {
        load_save();
        return false;
    }
    Int integral_part = static_cast<Int>(digit) * (neg ? -1 : 1);
    if (digit != 0) {
        while (get_digit(digit)) {
            integral_part = integral_part * 10 + digit;
        }
    }
    out_int = integral_part;
    pop_save();
    return true;
}

Bool Parser::get_float(Float &out_float)
{
    push_save();
    Bool neg = require('-');
    Nat8 digit;
    if (!get_digit(digit)) {
        load_save();
        return false;
    }
    Int integral_part = static_cast<Float>(digit) * (neg ? -1 : 1);
    if (digit != 0) {
        while (get_digit(digit)) {
            integral_part = integral_part * 10 + digit;
        }
    }
    Float fractional_part = 0.0f;
    if (require('.')) {
        if (!get_digit(digit)) {
            load_save();
            return false;
        }
        fractional_part = static_cast<Float>(digit) / 10;
        while (get_digit(digit)) {
            fractional_part = (fractional_part + digit) / 10;
        }
    }
    out_float = integral_part + fractional_part;
    pop_save();
    return true;
}

Bool Parser::get_number(std::variant<Int, Float> &out_number)
{
    push_save();
    Bool neg = require('-');
    Nat8 digit;
    if (!get_digit(digit)) {
        load_save();
        return false;
    }
    Int integral_part = static_cast<Int>(digit) * (neg ? -1 : 1);
    if (digit != 0) {
        while (get_digit(digit)) {
            integral_part = integral_part * 10 + digit;
        }
    }
    Bool is_float = false;
    Float fractional_part = 0.0f;
    if (require('.')) {
        is_float = true;
        if (!get_digit(digit)) {
            load_save();
            return false;
        }
        fractional_part = static_cast<Float>(digit) / 10;
        while (get_digit(digit)) {
            fractional_part = (fractional_part + digit) / 10;
        }
    }

    if (is_float) {
        Float number = static_cast<Float>(integral_part);
        number += fractional_part;
        out_number = number;
    } else {
        out_number = integral_part;
    }
    pop_save();
    return true;
}
}  // namespace Parsing