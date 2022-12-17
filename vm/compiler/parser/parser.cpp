#include <iostream>
#include "parser.h"
#include "tokenizer.h"

void frogl::parser::parse(frogl::source &source) {
    int line_number = 0;

    frogl::tokenizer tokenizer(" '\"\t\n(){}[]:;!?/\\&%^+*-=><.,");

    while (source.has_next()) {
        line_number++;
        std::string line = source.get_line();
        tokenizer.tokenize(line);

        char delim = 0;

        while (tokenizer.has_next()) {
            if (tokenizer.string_length() == 0) {
                if (tokenizer.get_delimiter() == '=')
                    std::cout << "= ";
                continue;
            }
            std::cout << tokenizer.get_next() << " ";
        }

    }
}
