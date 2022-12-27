#pragma once

#include <sstream>
#include "source.h"
#include "sliced_string.h"

namespace frogl {
    class string_source : public frogl::source {
    private:
        std::string *source;
        std::string source_name;
        sliced_string line;
        int left_border = 0;

    public:
        explicit string_source(std::string *source, std::string name);

        bool find_line() override;

        std::string name() override;
        frogl::sliced_string& get_line() override;
    };
}
