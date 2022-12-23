#pragma once

#include <sstream>
#include "source.h"

namespace frogl {
    class string_source : public frogl::source {
    private:
        std::string *source;
        std::string line;
        int left_border;
        int right_border;
    public:
        explicit string_source(std::string *source);

        bool has_next() override;

        std::string& get_line() override;
    };
}
