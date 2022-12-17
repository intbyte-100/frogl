#pragma once


#include <string>

namespace frogl {
    class tokenizer {
        const char *delimiters;
        int left_border;
        int right_border;
        std::string *string;
        char delimiter;
        bool next;

    public:
        tokenizer(const char *delimiters);

        char get_delimiter();
        bool has_next();
        std::string get_next();
        int string_length();
        char tokenize(std::string &string);
    };
}


