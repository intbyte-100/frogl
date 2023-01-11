#pragma once

#include "../../compiler/translator/const_table.h"
#include "retval_args_buffer.h"

namespace frogl {
    class context {
    public:
        frogl::retval_args_buffer *retval_args_buffer;
        byte *const_table;
        byte *table;
        int status = 1;

        inline context(frogl::retval_args_buffer *retval_args_buffer,
                       byte *const_table,
                       byte *table) : retval_args_buffer(retval_args_buffer), const_table(const_table), table(table) {}

    };
}

