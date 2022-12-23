#pragma once


#include <string>

namespace frogl {
    constexpr int QUOTATION_IS_NOT_CLOSED = 1;

    class tokenizer {
        const char *delimiters = " '\t\n(){}[]:;!?/\\&%^+*-=><.,";
        int left_border;
        int right_border;
        std::string *string;
        char delimiter;
        bool quotation_is_open;
        int status = 0;
    public:

        char get_delimiter() const;
        int get_status() const;
        bool find_next();
        std::string get_next();
        int string_length() const;
        char tokenize(std::string &string);
    };
}


