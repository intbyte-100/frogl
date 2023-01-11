#include <iostream>
#include "compiler/parser/tokenizer.h"
#include "compiler/translator/fbc_buffer.h"
#include "compiler/translator/const_table.h"
#include "compiler/parser/parser.h"
#include "compiler/string_source.h"
#include "compiler/sliced_string.h"
#include "vm/lambda.h"

void vm_test() {
    frogl::const_table const_table(0);


    frogl::fbc_buffer buffer;

    buffer.getai32(0, 0);
    buffer.getai32(1, 1);
    buffer.addi32(0, 0, 1);
    buffer.reti32(0);

    frogl::lambda<int, int, int> sum(&const_table.at<frogl::byte>(0), 8, buffer.pointer());


    std::cout << sum(1000, -7) << "\n";
}

int main()
{
    std::string code = "var a123 = 345 + 222\n"
                       "let c = 2345";

    //frogl::parser parser;
    //frogl::string_source source(&code, "test.frogl");

    //parser.parse(&std::cout, &source);
    //auto tokens = parser.get_tokens();

    auto sliced = frogl::sliced_string(&code, 0, code.size());
    frogl::tokenizer tokenizer;
    tokenizer.tokenize(sliced);

    while (tokenizer.has_next()) {
        auto token = tokenizer.get_token().to_string();
        std::cout << "token type: "
                  << frogl::token_type_to_string((frogl::token_types) tokenizer.get_token_type())
                  << "; token: '" << token << "'\n";
    }
    return 0;
}
