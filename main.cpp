#include <iostream>
#include "PostfixExpressionBuilder.h"

int main() {
    std::string s = "2+3*6-10 /15 ^(10-7* 20*sin(3.14) + ln(100))";
    auto p = PostfixExpressionBuilder::buildPostfixException(s);
    std::cout << p.getPostfixFormString() << std::endl;
    std::cout << p.evaluate() << std::endl;

    return 0;
}
