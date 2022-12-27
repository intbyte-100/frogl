#pragma once

#include <string>

namespace frogl {
    struct compiler_context {
    public:
        int line{};
        int current_symbol_index;
        std::string file_name;
        std::ostream *error_stream{};
        bool compilation_is_failed = false;
    };
}
