#pragma once

namespace frogl {
    class retval_args_buffer {
    public:
        void* retval;
        void* args[];
    };
}
