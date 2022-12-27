#pragma once


#include <string>
#include "../sliced_string.h"

namespace frogl {
    constexpr int QUOTATION_IS_NOT_CLOSED = 1;

    class tokenizer {
        const char *delimiters = " '\t\n(){}[]:;!?/\\&%^+*-=><.,";
        int left_border;
        int right_border;
        frogl::sliced_string *string;
        char delimiter;
        bool quotation_is_open;


        int status = 0;
    public:
        int quotation_opened_index;

        char get_delimiter() const;
        int get_status() const;
        bool find_token();
        frogl::sliced_string get_token();
        int string_length() const;
        char tokenize(frogl::sliced_string &string);
    };
}


