//
// Created by k17 on 26.12.2022.
//

#ifndef CPPLAB3_3_POSTFIXEXPRESSIONBUILDER_H
#define CPPLAB3_3_POSTFIXEXPRESSIONBUILDER_H


#include <cmath>
#include "PostfixExpression.h"
typedef std::function<double(double, double)> binFunction;
typedef std::function<double(double)> unaryFunction;
typedef struct {
    int priority = -1;
    binFunction operation;
} binOperator;

class PostfixExpressionBuilder {
public:
    friend class PostfixExpression;
    static PostfixExpression buildPostfixException(const std::string &infixExpressionString);
private:
    static const std::unordered_map<char, binOperator> binaryOperators;
    static const std::unordered_map<std::string, unaryFunction> unaryFunctions;
    static const std::unordered_map<std::string, unaryFunction> postfixFunctions;

    static void ParseTokens(std::stringstream &stream, std::vector<ExpressionToken> &infixTokens,
                            std::unordered_map<std::string, double> &variables);

    static bool isExpressionValid(const std::vector<ExpressionToken> &infixTokens);

    static std::vector<ExpressionToken> ConvertToPostfix(std::vector<ExpressionToken> infix);
};


#endif //CPPLAB3_3_POSTFIXEXPRESSIONBUILDER_H
