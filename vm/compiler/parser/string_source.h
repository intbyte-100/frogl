#pragma once

#include <sstream>
#include "source.h"

namespace frogl {
    class string_source : public frogl::source {
    private:
        std::stringstream stream;
        std::string line;
    public:
        string_source(std::string &source);

        virtual bool has_next();

        virtual std::string& get_line();
    };
}
