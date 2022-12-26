//
// Created by k17 on 26.12.2022.
//

#ifndef CPPLAB3_3_EXPRESSIONTOKEN_H
#define CPPLAB3_3_EXPRESSIONTOKEN_H


#include <string>
#include <functional>
#include <limits>
#include <stdexcept>



enum tokenType {
    CONSTANT,
    VARIABLE,
    PREFIX_FUNCTION,
    POSTFIX_FUNCTION, // like ! (factorial)
    BINARY_OPERATOR,
    OPEN_BRACKET,
    CLOSED_BRACKET
};

class ExpressionToken {
public:
    tokenType getType() const;

    const std::string &getStringRepresentation() const;

    const std::function<double(double, double)> *getBinFunc() const;

    const std::function<double(double)> *getFunc() const;

    int getOperationPriority() const;

    double getValue() const;

private:
    tokenType type;
    std::string stringRepresentation;
    const std::function<double(double, double)> *binFunc = nullptr;
    const std::function<double(double)> *func = nullptr;
    int operationPriority = -1;
    double value = std::numeric_limits<double>::quiet_NaN();
public:
    ExpressionToken() = default;
    // value (tokenType = CONSTANT)
    ExpressionToken(double value);
    //variable (tokenType = VARIABLE)
    ExpressionToken(const std::string &variableName);
    // function (tokenType = PREFIX_FUNCTION, POSTFIX_FUNCTION):
    ExpressionToken(tokenType type, const std::string &funcName, const std::function<double(double)> *function);
    // binary operation (tokenType = BINARY_OPERATOR)
    ExpressionToken(char operatorName, const std::function<double(double, double)> *func, int priority);
    // brackets (tokenType = OPEN_BRACKET, CLOSE_BRACKET)
    ExpressionToken(tokenType type);
};


#endif //CPPLAB3_3_EXPRESSIONTOKEN_H
