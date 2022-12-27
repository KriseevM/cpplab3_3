//
// Created by k17 on 26.12.2022.
//

#ifndef CPPLAB3_3_POSTFIXEXPRESSIONBUILDER_H
#define CPPLAB3_3_POSTFIXEXPRESSIONBUILDER_H


#include <cmath>
#include "PostfixExpression.h"

class PostfixExpressionBuilder {
public:
    static PostfixExpression buildPostfixException(const std::string &infixExpressionString);
private:

    static std::vector<ExpressionToken> ConvertToPostfix(std::vector<ExpressionToken> infix);
};


#endif //CPPLAB3_3_POSTFIXEXPRESSIONBUILDER_H
