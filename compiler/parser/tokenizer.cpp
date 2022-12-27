#include "tokenizer.h"



char frogl::tokenizer::tokenize(frogl::sliced_string &string) {
    this->string = &string;
    left_border = 0;
    right_border = -1;
    status = 0;
    quotation_is_open = false;
    quotation_opened_index = 0;
}

bool frogl::tokenizer::find_token() {

    const char *str = string->c_str();

    for (int i = right_border + 1; i < string->size() + 1; i++) {

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
            quotation_opened_index = i;
        }


        if (quotation_is_open)
            continue;

        //find other tokens by the delimiters
        while (delim[0] != '\0') {
            if (delim[0] == str[i] || i == string->size() - 1){

                left_border = right_border + 1;
                right_border = i;
                delimiter = delim[0];

                return true;
            }

            delim++;
        }
    }

    if (quotation_is_open)
        status = QUOTATION_IS_NOT_CLOSED;

    delimiter = '\0';
    return false;
}

frogl::sliced_string frogl::tokenizer::get_token() {
    return {string, left_border, right_border - left_border};
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

