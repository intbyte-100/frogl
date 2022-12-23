#pragma once

#include <string>

namespace frogl {

    enum class token_type {
        NAME,
        LITERAL,
        VARIABLE,
        CONST,
        BRACE_OPEN,
        BRACE_CLOSE,
        BEGIN,
        END,
        PLUS,
        MINUS,
        EQUALS,
        INTEGER
    };

    class token_data {
        void* value;

    public:
        template<typename T>
        inline void set_value(T val){
            value = (void* ) val;
        }

        template<typename T>
        inline T get_value(){
            return (T) value;
        }
    };


    class token {
    public:
        token_type type;
        token_data data;
        token_data value;
    };
}

