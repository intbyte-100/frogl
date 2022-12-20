#include "tokenizer.h"



char frogl::tokenizer::tokenize(std::string &string) {
    this->string = &string;
    left_border = 0;
    right_border = -1;
}

bool frogl::tokenizer::find_next() {

    const char *str = string->c_str();

    for (int i = right_border + 1; string != nullptr && i < string->size() + 1; i++) {

        const char* delim = delimiters;

        //if char is in the range from a to Z, then is cannot be delimiter for a token, so we can just pass iteration
        if (str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z')
            continue;

        //check if is start or end of quotation token
        if (str[i] == '"' && !(i != 0 && str[i - 1] == '\\')){
            if (quotation_is_open) {
                right_border = i;
                delimiter = '"';
                quotation_is_open = false;
                return true;
            }
            left_border = i + 1;
            quotation_is_open = true;
        }


        if (quotation_is_open)
            continue;

        //find other tokens by the delimiters
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

    if (quotation_is_open)
        status = QUOTATION_IS_NOT_CLOSE;

    delimiter = '\0';
    return false;
}

std::string frogl::tokenizer::get_next() {
    return string->substr(left_border, right_border - left_border);
}

char frogl::tokenizer::get_delimiter() const {
    return delimiter;
}

int frogl::tokenizer::string_length() const {
    return right_border - left_border;
}

int frogl::tokenizer::get_status() const {
    return status;
}

