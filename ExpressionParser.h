//
// Created by k17 on 27.12.2022.
//

#ifndef CPPLAB3_3_EXPRESSIONPARSER_H
#define CPPLAB3_3_EXPRESSIONPARSER_H

#include <functional>
#include <cmath>
#include "PostfixExpression.h"

typedef std::function<double(double, double)> binFunction;
typedef std::function<double(double)> unaryFunction;
typedef struct {
    int priority = -1;
    binFunction operation;
} binOperator;

class ExpressionParser {
    static const std::unordered_map<char, binOperator> binaryOperators;

    static const std::unordered_map<std::string, unaryFunction> unaryFunctions;
    static const std::unordered_map<std::string, unaryFunction> postfixFunctions;

public:
    static void ParseTokens(std::stringstream &stream, std::vector<ExpressionToken> &infixTokens,
                            std::unordered_map<std::string, double> &variables);
    friend class PostfixExpression;
};


#endif //CPPLAB3_3_EXPRESSIONPARSER_H
