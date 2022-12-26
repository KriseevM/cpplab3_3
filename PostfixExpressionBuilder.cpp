//
// Created by k17 on 26.12.2022.
//

#include <sstream>
#include "PostfixExpressionBuilder.h"
#include "TStack.h"
#include <cmath>
#include <iostream>

double factorial(int n)
{
    double res = 1.0;
    for(int i = 1; i < n; ++i)
    {
        res *= i+1;
    }
    return res;
}

const std::unordered_map<char, binOperator> PostfixExpressionBuilder::binaryOperators = {
        {'+', { 1, ([](double a, double b){ return a+b; } ) }},
        {'-', { 1, ([](double a, double b){ return a-b; } ) }},
        {'*', { 2, ([](double a, double b){ return a*b; } ) }},
        {'/', { 2, ([](double a, double b){ return a/b; } ) }},
        {'^', { 3, ([](double a, double b){ return std::pow(a, b); } ) }}
};

const std::unordered_map<std::string, unaryFunction> PostfixExpressionBuilder::unaryFunctions = {
        {"sin", [](double a){return sin(a); }},
        {"cos", [](double a){return cos(a); }},
        {"tg", [](double a){return tan(a); }},
        {"ctg", [](double a){return cos(a)/sin(a); }},
        {"sqrt", [](double a){return sqrt(a);}},
        {"ln", [](double a){return log(a); }}
};
const std::unordered_map<std::string, unaryFunction> PostfixExpressionBuilder::postfixFunctions = {
        {"!", [](double a){return factorial((int) a); }}
};

PostfixExpression PostfixExpressionBuilder::buildPostfixException(const std::string &infixExpressionString) {
    auto expr = PostfixExpression(infixExpressionString);
    std::stringstream stream(infixExpressionString);
    std::vector<ExpressionToken> infixTokens;
    infixTokens.reserve(infixExpressionString.size());
    std::unordered_map<std::string, double> variables;
    ParseTokens(stream, infixTokens, variables);
    if(!isExpressionValid(infixTokens))
    {
        throw std::invalid_argument("Invalid infix form given");
    }
    std::vector<ExpressionToken> postfixTokens = ConvertToPostfix(infixTokens);
    std::stringstream postfixStream;
    for(auto &p : postfixTokens)
    {
        postfixStream << p.getStringRepresentation() << " ";
    }
    expr.postfixFormString = postfixStream.str();
    expr.tokens = postfixTokens;
    expr.variables = variables;
    return expr;
}

bool PostfixExpressionBuilder::isExpressionValid(const std::vector<ExpressionToken> &infixTokens) {
    int openBrackets = 0;
    for (int i = 0; i+1 < infixTokens.size(); ++i)
    {
        switch(infixTokens[i].getType()) {
            case OPEN_BRACKET:
                switch(infixTokens[i+1].getType())
                {
                    case CONSTANT:
                    case VARIABLE:
                    case PREFIX_FUNCTION:
                    case OPEN_BRACKET:
                        break;
                    default:
                        return false;
                }
                openBrackets++;
                break;
            case CLOSED_BRACKET:
                switch(infixTokens[i+1].getType())
                {
                    case BINARY_OPERATOR:
                    case POSTFIX_FUNCTION:
                    case CLOSED_BRACKET:
                        break;
                    default:
                        return false;
                }
                openBrackets--;
                break;
            case CONSTANT:
            case VARIABLE:
            case POSTFIX_FUNCTION:
                switch(infixTokens[i+1].getType())
                {
                    case CLOSED_BRACKET:
                    case BINARY_OPERATOR:
                        break;
                    default:
                        return false;
                }
                break;
            case PREFIX_FUNCTION:
                if(infixTokens[i+1].getType() != OPEN_BRACKET)
                    return false;
                break;
            case BINARY_OPERATOR:
                switch(infixTokens[i+1].getType())
                {
                    case OPEN_BRACKET:
                    case CONSTANT:
                    case VARIABLE:
                    case PREFIX_FUNCTION:
                        break;
                    default:
                        return false;
                }
                break;
        }
    }
    if(infixTokens.back().getType() == CLOSED_BRACKET)
    {
        openBrackets--;
    }
    if(openBrackets > 0)
        return false;
    return true;
}

void PostfixExpressionBuilder::ParseTokens(std::stringstream &stream, std::vector<ExpressionToken> &infixTokens,
                                           std::unordered_map<std::string, double> &variables) {
    while((stream >> std::ws).good())
    {
        char c = stream.peek();
        if(binaryOperators.find(c) != binaryOperators.end())
        {
            binOperator op = binaryOperators.at(c);
            infixTokens.emplace_back(c, &op.operation, op.priority);
            stream >> c;
            continue;
        }
        double val;
        if(stream >> val)
        {
           infixTokens.emplace_back(val);
           continue;
        }
        stream.clear(stream.rdstate() & (~std::istream::failbit)); // clear failbit so we can try read again
        std::string funcName;
        int funcNameSize = 0;
        while(stream.good() && funcNameSize < 6) {
            c = stream.peek();
            if((c - '0' >= 0 && c - '0' <= 9) || c == ' ' || c == '(' || c == ')')
            {
                break;
            }
            else {
                funcName += c;
                stream.seekg(1, std::ios_base::cur);
                ++funcNameSize;
            }
        }
        if(!funcName.empty()) {
            if (unaryFunctions.find(funcName) != unaryFunctions.end()) {
                infixTokens.emplace_back(PREFIX_FUNCTION, funcName, &unaryFunctions.at(funcName));
                continue;
            }
            if (postfixFunctions.find(funcName) != postfixFunctions.end())
            {
                infixTokens.emplace_back(POSTFIX_FUNCTION, funcName, &unaryFunctions.at(funcName));
                continue;
            }
            variables.insert(std::pair<std::string, double>(funcName, std::numeric_limits<double>::quiet_NaN()));
            infixTokens.emplace_back(funcName);
            continue;
        }
        stream << c;
        stream.ignore(1);
        switch(c)
        {
            case '(':
                infixTokens.emplace_back(OPEN_BRACKET);
                break;
            case ')':
                infixTokens.emplace_back(CLOSED_BRACKET);
                break;
            default:
                break;
        }
    }
}

std::vector<ExpressionToken> PostfixExpressionBuilder::ConvertToPostfix(std::vector<ExpressionToken> infix) {
    TStack<ExpressionToken> tokenStack;
    std::vector<ExpressionToken> postfix;
    for(ExpressionToken token : infix)
    {
        switch(token.getType())
        {
            case CONSTANT:
            case VARIABLE:
            case POSTFIX_FUNCTION:
                postfix.emplace_back(token);
                break;
            case PREFIX_FUNCTION:
            case OPEN_BRACKET:
                tokenStack.Push(token);
                break;
            case CLOSED_BRACKET:
                while(tokenStack.Top().getType() != OPEN_BRACKET)
                {
                    postfix.emplace_back(tokenStack.Top());
                    tokenStack.Pop();
                }
                tokenStack.Pop();
                break;
            case BINARY_OPERATOR:
                while(!tokenStack.isEmpty() && (tokenStack.Top().getType() == PREFIX_FUNCTION ||
                      (tokenStack.Top().getType() == BINARY_OPERATOR &&
                      tokenStack.Top().getOperationPriority() >= token.getOperationPriority())))
                {
                    postfix.emplace_back(tokenStack.Top());
                    tokenStack.Pop();
                }
                tokenStack.Push(token);
                break;
        }
    }
    while(!tokenStack.isEmpty())
    {
        postfix.emplace_back(tokenStack.Top());
        tokenStack.Pop();
    }
    return postfix;
}
