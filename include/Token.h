#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType
{
    NUMBER,
    OPERATOR,
    FUNCTION,
    L_PAREN,
    R_PAREN
};

struct Token
{
    std::string value;
    TokenType type;

    Token(std::string val, TokenType t) : value(val), type(t) {}
};


#endif