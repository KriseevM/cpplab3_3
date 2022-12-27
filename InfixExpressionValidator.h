//
// Created by k17 on 27.12.2022.
//

#ifndef CPPLAB3_3_INFIXEXPRESSIONVALIDATOR_H
#define CPPLAB3_3_INFIXEXPRESSIONVALIDATOR_H


#include <cmath>
#include "PostfixExpression.h"

class InfixExpressionValidator {

public:
    static bool isExpressionValid(const std::vector<ExpressionToken> &infixTokens);
};


#endif //CPPLAB3_3_INFIXEXPRESSIONVALIDATOR_H
