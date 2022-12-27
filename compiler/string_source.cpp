#include "string_source.h"

frogl::string_source::string_source(std::string *source, std::string name) {
    this->source = source;
    this->source_name = name;
}

bool frogl::string_source::find_line() {
    auto str = source->c_str();
    int last_index = (int) source->size() - 1;

    for (int i = left_border; i < source->size(); ++i) {
        if (str[i] == '\n' || str[i] == '\r') {
            line = sliced_string(source, left_border, i - left_border);
            left_border = i + 1;
            return true;
        } else if (i == last_index) {
            line = sliced_string(source, left_border, i - left_border + 1);
            left_border = i + 1;
            return true;
        }
    }
    return false;
}

frogl::sliced_string &frogl::string_source::get_line() {
    return line;
}

std::string frogl::string_source::name() {
    return source_name;
}
