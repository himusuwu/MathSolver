#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"

class Parser
{
    public:
        std::vector<Token> convert(const std::vector<Token>& tokens);

    private:
        int precedence(const Token& token);
};

#endif