cmake_minimum_required(VERSION 3.20)
project(cpplab3_3)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_executable(cpplab3_3 main.cpp ExpressionToken.cpp ExpressionToken.h PostfixExpression.cpp PostfixExpression.h PostfixExpressionBuilder.cpp PostfixExpressionBuilder.h TStack.h ExpressionParser.cpp ExpressionParser.h InfixExpressionValidator.cpp InfixExpressionValidator.h Table.h)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
        ExpressionsTests
        Tests/TStackTests.cpp Tests/ExpressionTests.cpp
        ExpressionToken.cpp ExpressionToken.h PostfixExpression.cpp PostfixExpression.h PostfixExpressionBuilder.cpp PostfixExpressionBuilder.h TStack.h ExpressionParser.cpp ExpressionParser.h InfixExpressionValidator.cpp InfixExpressionValidator.h Table.h)
target_link_libraries(
        ExpressionsTests
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(ExpressionsTests)