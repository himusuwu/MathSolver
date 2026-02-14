#include <iostream>
#include <stack>
#include <string>

#include "Lexer.h"

bool Lexer::isOperator(char c)
{
    return(std::string("+-*/").find(c) != std::string::npos);
}

std::vector<Token> Lexer::tokenize(const std::string& expression)
{
    std::vector<Token> tokens;

    size_t i = 0;

    while(i < expression.size())
    {
        char c = expression[i];

        if(std::isspace(c))
        {
            i++;
            continue;
        }

        if(std::isdigit(c) || c == '.')
        {
            std::string number;
            bool dotUsed = false;

            while(i < expression.size() && (std::isdigit(expression[i]) || expression[i] == '.'))
            {
                if(expression[i] == '.')
                {
                    if(dotUsed)
                    {
                        throw std::runtime_error("Error: Double digit used.");
                    }

                    dotUsed = true;
                }

                number += expression[i];
                i++;
            }

            tokens.push_back({number, TokenType::NUMBER});
            continue;
        }

        if(std::isalpha(c))
        {
            std::string func;

            while(i < expression.size() && std::isalpha(expression[i]))
            {
                func += expression[i];
                i++;
            }

            tokens.push_back({func, TokenType::FUNCTION});
            continue;
        }

        if(isOperator(c))
        {
            tokens.push_back({std::string(1, c), TokenType::OPERATOR});
            i++;
            continue;
        }
        else if(c == '(')
        {
            tokens.push_back({"(", TokenType::L_PAREN});
            i++;
            continue;
        }
        else if(c == ')')
        {
            tokens.push_back({")", TokenType::R_PAREN});
            i++;
            continue;
        }

        throw std::runtime_error("Error: Invalid character.");
    }

    return tokens;
}