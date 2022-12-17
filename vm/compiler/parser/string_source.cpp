//
// Created by intbyte on 12/15/22.
//

#include "string_source.h"

frogl::string_source::string_source(std::string &source) {
    stream = std::stringstream(source);
}

bool frogl::string_source::has_next() {
    return std::getline(stream, line, '\n').operator bool();
}

std::string &frogl::string_source::get_line() {
    return line;
}
