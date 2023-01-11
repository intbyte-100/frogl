#pragma once

#include <list>
#include "../token.h"

namespace frogl {
    class translator {
    public:
        void translate(std::list<token*> *tokens);
    };
}
