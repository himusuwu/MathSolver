#include <iostream>
#include "Lexer.h"
#include "Parser.h"

int main()
{
    Lexer lexer;
    Parser parser;

    std::string expression = "3 + sin(4 * 2)";

    auto tokens = lexer.tokenize(expression);

    auto onp = parser.convert(tokens);

    std::cout << "ONP : ";

    for(const auto& token : onp)
    {
        std::cout << token.value << " ";
    }

    std::cout << std::endl;

    return 0;
}