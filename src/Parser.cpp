#include "Parser.h"
#include <stack>

int Parser::precedence(const Token& token)
{
    if(token.type == TokenType::FUNCTION)
    {
        return 3;
    }

    if(token.type == TokenType::OPERATOR)
    {
        if(token.value == "*" || token.value == "/")
        {
            return 2;
        }
        else if(token.value == "+" || token.value == "-")
        {
            return 1;
        }
    }

    return 0;
}

std::vector<Token> Parser::convert(const std::vector<Token>& tokens)
{
    std::vector<Token> output;
    std::stack<Token> operators;

    for(const Token& token : tokens)
    {
        if(token.type == TokenType::NUMBER)
        {
            output.push_back(token);
        }

        else if(token.type == TokenType::FUNCTION)
        {
            operators.push(token);
        }

        else if(token.type == TokenType::OPERATOR)
        {
            while(!operators.empty() 
                && (precedence(operators.top()) >= precedence(token)))
            {
                output.push_back(operators.top());
                operators.pop();
            }

            operators.push(token);
        }

        else if(token.type == TokenType::L_PAREN)
        {
            operators.push(token);
        }

        else if(token.type == TokenType::R_PAREN)
        {
            while(!operators.empty() 
                && (operators.top().type != TokenType::L_PAREN))
            {
                output.push_back(operators.top());
                operators.pop();
            }

            operators.pop();

            if(!operators.empty() 
                && (operators.top().type == TokenType::FUNCTION))
            {
                output.push_back(operators.top());
                operators.pop();
            }
        }
    }

    while(!operators.empty())
    {
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}