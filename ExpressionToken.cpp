//
// Created by k17 on 26.12.2022.
//

#include "ExpressionToken.h"

ExpressionToken::ExpressionToken(tokenType type) : type(type) {
    switch (type) {
        case OPEN_BRACKET:
            stringRepresentation = "(";
            break;
        case CLOSED_BRACKET:
            stringRepresentation = ")";
            break;
        default:
            throw std::invalid_argument("TokenType-only-initialized token can only accept brackets tokenType");
    }
}

ExpressionToken::ExpressionToken(
        tokenType type,
        const std::string &funcName,
        const std::function<double(double)> *function)
        : type(type), stringRepresentation(funcName), func(function)
{
    switch(type) {
        case PREFIX_FUNCTION:
        case POSTFIX_FUNCTION:
            break;
        default:
            throw std::invalid_argument("Function-initialized token constructor can only accept PREFIX_FUNCTION,"
                                        " POSTFIX_FUNCTION and BINARY_OPERATOR token types");
    }
}

ExpressionToken::ExpressionToken(const std::string &variableName) : type(VARIABLE), stringRepresentation(variableName){}
ExpressionToken::ExpressionToken(double value) : type(CONSTANT), stringRepresentation(std::to_string(value)), value(value) {}
ExpressionToken::ExpressionToken(char operatorName, const std::function<double(double, double)> *func, int priority)
: type(BINARY_OPERATOR), stringRepresentation(1, operatorName), binFunc(func), operationPriority(priority){}

tokenType ExpressionToken::getType() const {
    return type;
}

const std::string &ExpressionToken::getStringRepresentation() const {
    return stringRepresentation;
}

const std::function<double(double, double)> *ExpressionToken::getBinFunc() const {
    return binFunc;
}

const std::function<double(double)> *ExpressionToken::getFunc() const {
    return func;
}

int ExpressionToken::getOperationPriority() const {
    return operationPriority;
}

double ExpressionToken::getValue() const {
    return value;
}
