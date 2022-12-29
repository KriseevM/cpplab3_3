//
// Created by k17 on 26.12.2022.
//

#ifndef CPPLAB3_3_POSTFIXEXPRESSION_H
#define CPPLAB3_3_POSTFIXEXPRESSION_H


#include <vector>
#include <unordered_map>
#include "ExpressionToken.h"
#include "Table.h"

class PostfixExpression {
private:
    PostfixExpression(const std::string &originalExpressionString);
    std::vector<ExpressionToken> tokens;
    std::string postfixFormString;
    const std::string originalExpressionString;
    Table<std::string, double> variables;
public:
    const std::string &getPostfixFormString() const;
    const std::string &getOriginalExpressionString() const;
    std::vector<std::string> getVariableNames() const;
    double evaluate();
    void setVariable(const std::string &variableName, double value);
    double getVariableValue(const std::string &variableName);
    friend class PostfixExpressionBuilder;

    double ExtractTokenValue(ExpressionToken &token);
};


#endif //CPPLAB3_3_POSTFIXEXPRESSION_H
