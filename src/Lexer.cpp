#include <iostream>
#include <stack>
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

class Lexer
{
    public:
        std::vector<Token> convert(const std::string& expression);

    private:
        std::vector<Token> tokenize(const std::string& expression);
        int precedence(const std::string& op);
};

std::vector<Token> Lexer::tokenize(const std::string& expression)
{
    std::vector<Token> tokens;

    for(size_t i = 0; i < expression.length(); i++)
    {
        if(std::isspace(expression[i]))
        {
            i++;
            continue;
        }

        if(std::isdigit(expression[i]) || expression[i] == '.')
        {
            std::string number;
            bool dotUsed = false;

            while(i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.'))
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

        if(std::string("+-*/").find(expression[i]) != std::string::npos)
        {
            tokens.push_back({std::string(1, expression[i]), TokenType::OPERATOR}); //change char to string
            i++;
            continue;
        }

        if(expression[i] == '(')
        {
            tokens.push_back({std::string(1, expression[i]), TokenType::L_PAREN});
            i++;
            continue;
        }

        if(expression[i] == ')')
        {
            tokens.push_back({std::string(1, expression[i]), TokenType::R_PAREN});
            i++;
            continue;
        }

        if(std::isalpha(expression[i]))
        {
            std::string func;

            while(i < expression.length() && std::isalpha(expression[i]))
            {
                func += expression[i];
                i++;
            }

            tokens.push_back({func, TokenType::FUNCTION});
        }

        throw std::runtime_error("Error: Invalid character.");
    }

    return tokens;
}

int Lexer::precedence(const std::string& op)
{
    if(op == "+" || op == "-") return 1;
    if(op == "*" || op == "/") return 2;
    return 0;
}

std::vector<Token> Lexer::convert(const std::string& expression)
{
    std::vector<Token> tokens = tokenize(expression);
    std::vector<Token> output;
    std::stack<Token> operators;

    for(const auto& token : tokens)
    {
        if(token.type == TokenType::NUMBER)
        {
            output.push_back(token);
        }

        else if(token.type == TokenType::FUNCTION)
        {
            operators.push(token);
        }

        else if(token.type == TokenType::L_PAREN)
        {
            operators.push(token);
        }

        else if(token.type == TokenType::OPERATOR)
        {
            while(!operators.empty() && operators.top().type == TokenType::OPERATOR 
                && precedence(operators.top().value) >= precedence(token.value))
            {
                output.push_back(operators.top());
                operators.pop();
            }

            operators.push(token);
        }

        else if(token.type == TokenType::R_PAREN)
        {
            while(operators.top().type != TokenType::L_PAREN)
            {
                output.push_back(operators.top());
                operators.pop();
            }

            operators.pop();

            if(operators.top().type == TokenType::FUNCTION)
            {
                output.push_back(operators.top());
                operators.pop();
            }
        }

        while(!operators.empty())
        {
            output.push_back(operators.top());
            operators.pop();
        }
    }

    return output;
}