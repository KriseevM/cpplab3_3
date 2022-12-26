cmake_minimum_required(VERSION 3.25)
project(cpplab3_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpplab3_3 main.cpp ExpressionToken.cpp ExpressionToken.h PostfixExpression.cpp PostfixExpression.h PostfixExpressionBuilder.cpp PostfixExpressionBuilder.h TStack.h)
