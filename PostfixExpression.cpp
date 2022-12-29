//
// Created by k17 on 26.12.2022.
//

#include <cmath>
#include "PostfixExpression.h"
#include "TStack.h"
#include "PostfixExpressionBuilder.h"
#include "ExpressionParser.h"

double PostfixExpression::evaluate() {
    if(tokens.empty())
        return 0;
    TStack<ExpressionToken> tokenStack;
    ExpressionToken t;
    double op1, op2;
    std::function<double(double)> unaryFunc;
    for(auto &token : tokens)
    {
        switch(token.getType())
        {
            case CONSTANT:
            case VARIABLE:
                tokenStack.Push(token);
                break;
            case PREFIX_FUNCTION:
            case POSTFIX_FUNCTION:
                unaryFunc = *token.getFunc();
                op1 = ExtractTokenValue(tokenStack.Top());
                tokenStack.Pop();
                t = ExpressionToken(unaryFunc(op1));
                tokenStack.Push(t);
                break;
            case BINARY_OPERATOR:
                op2 = ExtractTokenValue(tokenStack.Top());
                tokenStack.Pop();
                op1 = ExtractTokenValue(tokenStack.Top());
                tokenStack.Pop();
                t = ExpressionToken(ExpressionParser::binaryOperators.at(token.getStringRepresentation()[0]).operation(op1, op2));
                tokenStack.Push(t);
                break;
            default:
                throw std::invalid_argument("Invalid token in postfix expression");
        }
    }
    if(tokenStack.getSize() != 1)
        throw std::invalid_argument("Could not get final result from exception");
    return tokenStack.Top().getValue();
}
PostfixExpression::PostfixExpression(const std::string &originalExpressionString) : originalExpressionString(originalExpressionString),
                                                                                    variables({}) {}
void PostfixExpression::setVariable(const std::string &variableName, double value) {
    if(!variables.find(variableName))
        throw std::out_of_range("Invalid variable name");
    variables.at(variableName) = value;
}

const std::string &PostfixExpression::getPostfixFormString() const {
    return postfixFormString;
}

const std::string &PostfixExpression::getOriginalExpressionString() const {
    return originalExpressionString;
}

double PostfixExpression::getVariableValue(const std::string &variableName) {
    return variables.at(variableName);
}

std::vector<std::string> PostfixExpression::getVariableNames() const{
    return variables.getKeys();
}

double PostfixExpression::ExtractTokenValue(ExpressionToken &token) {
    switch(token.getType())
    {
        case VARIABLE:
            if (std::isnan(variables.at(token.getStringRepresentation())))
                throw std::invalid_argument("variable \"" + token.getStringRepresentation() + "\" is not assigned yet");
            return variables.at(token.getStringRepresentation());
        case CONSTANT:
            return token.getValue();
        default:
            throw std::invalid_argument("Tried extracting value from non-value token");
    }
}