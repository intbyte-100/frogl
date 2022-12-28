#include <iostream>
#include "compiler/translator/fbc_buffer.h"
#include "vm/util/const_table.h"
#include "vm/lambda.h"
#include "compiler/parser/parser.h"
#include "compiler/string_source.h"
#include "compiler/sliced_string.h"


void vm_test(){
    frogl::const_table const_table(0);


    frogl::fbc_buffer buffer;

    buffer.getai32(0, 0);
    buffer.getai32(1, 1);
    buffer.addi32(0, 0, 1);
    buffer.reti32(0);

    frogl::lambda<int, int, int> sum(&const_table.at<frogl::byte>(0), 8, buffer.pointer());


    std::cout << sum(1000,-7) << "\n";
}

int main() {

    std::string code = "let a = 203 + 2\"\n"
                       "var c = 1ddfdswf + 33";


    frogl::parser parser;
    frogl::string_source source(&code, "test.frogl");


    parser.parse(&std::cout, &source);
    auto tokens = parser.get_tokens();

    return 0;
}
