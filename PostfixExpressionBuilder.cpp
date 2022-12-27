//
// Created by k17 on 26.12.2022.
//

#include <sstream>
#include "PostfixExpressionBuilder.h"
#include "TStack.h"
#include "ExpressionParser.h"
#include "InfixExpressionValidator.h"
#include <cmath>
#include <iostream>



PostfixExpression PostfixExpressionBuilder::buildPostfixException(const std::string &infixExpressionString) {
    auto expr = PostfixExpression(infixExpressionString);
    std::stringstream stream(infixExpressionString);
    std::vector<ExpressionToken> infixTokens;
    infixTokens.reserve(infixExpressionString.size());
    std::unordered_map<std::string, double> variables;
    ExpressionParser::ParseTokens(stream, infixTokens, variables);
    if(!InfixExpressionValidator::isExpressionValid(infixTokens))
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
