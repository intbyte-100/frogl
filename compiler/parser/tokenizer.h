#pragma once


#include <string>
#include "../sliced_string.h"

#define ENUM(name, ...) enum name
namespace frogl {
constexpr int QUOTATION_IS_NOT_CLOSED = 1;

enum token_types {
    WORD = 100,
    STRING = 101,
    LESS_OR_EQUAL = 103,
    BIGGER_OR_EQUAL = 104,
    AND = 105,
    OR = 106,
    NOT_EQUALS = 107,
    SPACE = ' ',
    SET = '=',
    LESS = '<',
    BIGGER = '>',
    SEMICOLON = ';',
    OPENED_BRACE = '(',
    CLOSED_BRACE = ')',
    PLUS = '+',
    MINUS = '-',
    QUOTATION_IS_NOT_CLOSED_ERROR,
    EQUALS,
    NOT = '!'

};

std::string token_type_to_string(token_types type);

class tokenizer
{
    const char *delimiters = " '\t\n(){}[]:;!?/\\&%^+*-=><.,";
    int left_border;
    int right_border;
    frogl::sliced_string *string;
    token_types token_type;
    bool quotation_is_open;
    int position;

    int status = 0;

public:
    int quotation_opened_index;

    char get_token_type() const;
    int get_status() const;
    bool has_next();
    frogl::sliced_string get_token();
    int string_length() const;
    void tokenize(frogl::sliced_string &string);
};
} // namespace frogl
