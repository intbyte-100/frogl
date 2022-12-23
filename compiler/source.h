#pragma once

#include <string>

namespace frogl {
    class source {
    public:
        virtual bool has_next() = 0;
        virtual std::string &get_line() = 0;
    };
}
