#include <iostream>
#include "parser.h"
#include "tokenizer.h"
#include "context.h"


inline bool is_integer(frogl::sliced_string &str){
    int i = 0;
    if (str[0] == '-')
        i++;
    for (; i < str.size(); i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return false;
    }

    return true;
}


inline void error(frogl::compiler_context *context, const std::string& line, int symbol_index){
    if (!context->compilation_is_failed) {
        *context->error_stream << "COMPILATION FAILED:\n";
        context->compilation_is_failed = true;
    }

    *context->error_stream << "at " << context->file_name << " (line " << context->line << "):\n\t" << line << "\n\t";

    for (int i = 0; i < symbol_index; ++i)
        *context->error_stream << ' ';

    *context->error_stream << "^\n";
}


void frogl::parser::parse(std::ostream *error_stream, frogl::source *source) {
    int line_number = 0;

    frogl::tokenizer tokenizer;

    compiler_context context;
    context.file_name = source->name();
    context.error_stream = error_stream;

    while (source->find_line()) {
        context.current_symbol_index = 0;
        line_number++;
        auto line = source->get_line();
        tokenizer.tokenize(line);

        context.line = line_number;



        while (tokenizer.find_token()) {
            auto token = tokenizer.get_token();

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
                else if (!(token[0] >= '0' && token[0] <= '9')){
                    new_token->type = token_type::NAME;
                    new_token->value.set_value(token.to_string_pointer());
                } else {
                    int symbol_index = token.c_str() - line.c_str() + token.size() / 2;
                    error(&context, line.to_string(), symbol_index);
                    *error_stream << "Invalid syntax: Unexpected token \"" << token.to_string() << "\"\n\n";
                }
            }
        }


        if (tokenizer.get_status() == QUOTATION_IS_NOT_CLOSED) {
            error(&context, line.to_string(), tokenizer.quotation_opened_index);
            *error_stream << "Invalid syntax: Quotation mark is not closed\n\n";
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
