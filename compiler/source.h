#pragma once

#include <string>
#include "sliced_string.h"

namespace frogl {
    class source {
    public:
        virtual std::string name() = 0;
        virtual bool find_line() = 0;
        virtual frogl::sliced_string &get_line() = 0;
    };
}
