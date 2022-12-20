#pragma once


#include <list>
#include "token.h"
#include "source.h"

namespace frogl {
    class parser {
        std::list<frogl::token> allocated_tokens;
        std::list<frogl::token> tokens;

    public:

        void parse(std::ostream &ostream, frogl::source &source);

        std::list<token> *get_tokens(){
            return &tokens;
        }


    };
}
