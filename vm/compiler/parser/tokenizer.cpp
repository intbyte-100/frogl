#include "tokenizer.h"

frogl::tokenizer::tokenizer(const char *delimiters) {
    this->delimiters = delimiters;
}

char frogl::tokenizer::tokenize(std::string &string) {
    this->string = &string;
    left_border = 0;
    right_border = -1;
    next = false;
}

bool frogl::tokenizer::has_next() {

    const char *str = string->c_str();

    for (int i = right_border + 1; string != nullptr && i < string->size() + 1; i++) {

        const char* delim = delimiters;

        if (str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z')
            continue;

        while (delim[0] != '\0') {
            if (delim[0] == str[i] || str[i] == 0){


                left_border = right_border + 1;
                right_border = i;
                delimiter = delim[0];


                return true;
            }

            delim++;
        }
    }

    delimiter = '\0';
    return false;
}

std::string frogl::tokenizer::get_next() {
    return string->substr(left_border, right_border - left_border);
}

char frogl::tokenizer::get_delimiter() {
    return delimiter;
}

int frogl::tokenizer::string_length() {
    return right_border - left_border;
}

