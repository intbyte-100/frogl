#include <iostream>
#include "parser.h"
#include "tokenizer.h"


struct parser_context {
public:
    int line{};
    std::string file_name;
    std::ostream *error_stream{};
    bool compilation_is_failed = false;
};

inline bool is_integer(std::string &str){
    int i = 0;
    if (str[0] == '-')
        i++;
    for (; i < str.size(); i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return false;
    }

    return true;
}

inline void error(parser_context &context){
    if (!context.compilation_is_failed) {
        *context.error_stream << "COMPILATION FAILED:\n";
        context.compilation_is_failed = true;
    }
    *context.error_stream << "  at " << context.file_name << " (line " << context.line << "):\n";
}


void frogl::parser::parse(std::ostream *error_stream, frogl::source *source) {
    int line_number = 0;

    frogl::tokenizer tokenizer;

    parser_context context;
    context.file_name = "main.frogl";
    context.error_stream = error_stream;

    while (source->has_next()) {
        line_number++;
        std::string line = source->get_line();
        tokenizer.tokenize(line);

        context.line = line_number;



        while (tokenizer.find_next()) {
            auto token = tokenizer.get_next();

            bool zero_size_token = tokenizer.string_length() == 0;

            if (zero_size_token && tokenizer.get_delimiter() == ' ')
                continue;

            auto new_token = new frogl::token();



            if (zero_size_token) {
                switch (tokenizer.get_delimiter()) {
                    case '(':
                        new_token->type = token_type::BRACE_OPEN;
                        break;
                    case ')':
                        new_token->type = token_type::BRACE_CLOSE;
                        break;
                    case '{':
                        new_token->type = token_type::BEGIN;
                        break;
                    case '}':
                        new_token->type = token_type::END;
                        break;
                    case '+':
                        new_token->type = token_type::PLUS;
                        break;
                    case '-':
                        new_token->type = token_type::MINUS;
                        break;
                    case '=':
                        new_token->type = token_type::EQUALS;
                        break;
                }
                tokens.push_back(new_token);
            } else {

                tokens.push_back(new_token);

                if (token == "let")
                    new_token->type = token_type::LITERAL;
                else if (token == "var")
                    new_token->type = token_type::VARIABLE;
                else if (is_integer(token))
                    new_token->type = token_type::INTEGER;
                else {
                    new_token->type = token_type::NAME;
                    new_token->value.set_value(new std::string(token));
                }
            }
        }


        if (tokenizer.get_status() == QUOTATION_IS_NOT_CLOSED) {
            error(context);
            *error_stream << "\t" << line << "\n\n";
            *error_stream << "Invalid syntax: Quotation mark is not closed";
        }

    }
}

frogl::parser::~parser() {
    for (auto token: tokens) {
        if (token->type == token_type::NAME)
            delete token->value.get_value<std::string*>();
        delete token;
    }
}
