#include "tokenizer.h"

template<typename T>
inline bool in_range(T value, T from, T to)
{
    return value >= from && value <= to;
}

void frogl::tokenizer::tokenize(frogl::sliced_string &string)
{
    this->string = &string;
    left_border = 0;
    right_border = -1;
    status = 0;
    quotation_is_open = false;
    quotation_opened_index = 0;
    position = 0;
}

bool frogl::tokenizer::has_next()
{
    return position < string->size();
}

frogl::sliced_string frogl::tokenizer::get_token() {
    int end = position - 1;

    auto str = string->c_str();
    while (end++ < string->size()) {
        while (str[end] == ' ' || str[end] == '\n')
            position = ++end;

        //string parsing
        if (str[end] == '"') {
            token_type = STRING;

            for (end++; end < string->size(); end++) {
                if (str[end] == '"') {
                    int pos = position;
                    position = end + 1;
                    return {string, pos + 1, end - position};
                }
            }
            token_type = QUOTATION_IS_NOT_CLOSED_ERROR;
            return sliced_string::empty();
        }

        bool is_operator = false;
        bool is_combined_operator = end + 1 < string->size() && str[end + 1] == '=';

        if ((is_operator = str[end] == '<'))
            token_type = is_combined_operator ? LESS_OR_EQUAL : LESS;
        else if ((is_operator = str[end] == '>'))
            token_type = is_combined_operator ? BIGGER_OR_EQUAL : BIGGER;
        else if ((is_operator = str[end] == '!'))
            token_type = is_combined_operator ? NOT_EQUALS : NOT;
        else if ((is_operator = str[end] == '='))
            token_type = is_combined_operator ? EQUALS : SET;

        if (is_operator) {
            int size = 1;

            if (is_combined_operator) {
                size++;
            }

            position = end + size;

            return {string, position - size, size};
        }

        token_type = WORD;

        int size = 0;

        while (end < string->size()) {
            if (str[end] != ' ' && str[end] != '\n') {
                end++;
                continue;
            }
            break;
        }

        int pos = position;
        position = end + 1;
        return {string, pos, end - pos};
    }
    return {string, left_border, right_border - left_border};
}

char frogl::tokenizer::get_token_type() const {
    return token_type;
}

int frogl::tokenizer::string_length() const {
    return right_border - left_border;
}

int frogl::tokenizer::get_status() const {
    return status;
}

std::string frogl::token_type_to_string(token_types type)
{
    switch (type) {
    case WORD:
        return "WORD";
    case STRING:
        return "STRING";
    case LESS_OR_EQUAL:
        return "LESS_OR_EQUAL";
    case BIGGER_OR_EQUAL:
        return "BIGGER_OR_EQUAL";
    case AND:
        return "AND";
    case OR:
        return "OR";
    case NOT_EQUALS:
        return "NOT_EQUALS";
    case SPACE:
        return "SPACE";
    case SET:
        return "SET";
    case LESS:
        return "LESS";
    case BIGGER:
        return "BIGGER";
    case SEMICOLON:
        return "SEMICOLON";
    case OPENED_BRACE:
        return "OPENED_BRACE";
    case CLOSED_BRACE:
        return "CLOSED_BRACE";
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case NOT:
        return "NOT";
    case EQUALS:
        return "EQUALS";
    default:
        return "UNKNOWN";
    }
}
