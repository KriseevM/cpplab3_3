#include <iostream>
#include "PostfixExpressionBuilder.h"

int main() {
    /*std::string s = "2+3*6-10 /15 ^(10-7* 20*sin(a) +    sqrt(100))";
    auto p = PostfixExpressionBuilder::buildPostfixException(s);
    p.setVariable("a", 10.0);
    std::cout << p.getPostfixFormString() << std::endl;
    std::cout << p.evaluate() << std::endl;*/

    std::vector<double> solutions;
    std::vector<PostfixExpression> expressions;
    for(int i = 0; i < 10; ++i)
    {
        expressions.push_back(
                PostfixExpressionBuilder::buildPostfixException("x^" + std::to_string(i+1)));
        expressions.back().setVariable("x", 2);
    }
    for(auto &e : expressions)
    {
        solutions.push_back(e.evaluate());
        std::cout << solutions.back() << " ";
    }
    return 0;
}
