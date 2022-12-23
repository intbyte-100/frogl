//
// Created by intbyte on 12/15/22.
//

#include "string_source.h"

frogl::string_source::string_source(std::string *source) {
    this->source = source;
}

bool frogl::string_source::has_next() {
    auto str = source->c_str();
    for (int i = left_border; i < source->size(); ++i) {
        if (str[i] == '\n' || str[i] == '\r') {
            line = source->substr(left_border, i - left_border);
            left_border = i + 1;
            return true;
        }
    }
    return false;
}

std::string &frogl::string_source::get_line() {
    return line;
}
