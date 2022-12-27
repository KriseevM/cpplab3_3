//
// Created by k17 on 27.12.2022.
//

#include <gtest/gtest.h>
#include "../PostfixExpressionBuilder.h"
#include "../ExpressionParser.h"
#include "../InfixExpressionValidator.h"

TEST(expression_parsing, constant_parsed)
{
    std::vector<ExpressionToken> tokens;
    std::unordered_map<std::string, double> vars;
    std::stringstream input("20.0045");
    ExpressionParser::ParseTokens(input, tokens, vars);
    EXPECT_EQ(CONSTANT, tokens[0].getType());
    EXPECT_EQ(20.0045, tokens[0].getValue());
}
TEST(expression_parsing, variable_parsed)
{
    std::vector<ExpressionToken> tokens;
    std::unordered_map<std::string, double> vars;
    std::stringstream input("abc");
    ExpressionParser::ParseTokens(input, tokens, vars);
    EXPECT_EQ(VARIABLE, tokens[0].getType());
    EXPECT_TRUE(vars.find("abc") != vars.end());
}



TEST(expression_validation, valid_expression_passes)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(2),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(3),
            ExpressionToken('*', nullptr, -1),
            ExpressionToken(PREFIX_FUNCTION, "sin", nullptr),
            ExpressionToken(OPEN_BRACKET),
            ExpressionToken("a"),
            ExpressionToken(CLOSED_BRACKET),
            ExpressionToken('/', nullptr, -1),
            ExpressionToken(4),
            ExpressionToken(POSTFIX_FUNCTION, "!", nullptr)
    }; // 2+3*sin(a)/4! must be valid
    EXPECT_TRUE(InfixExpressionValidator::isExpressionValid(tokens));
}
TEST(expression_validation, extra_open_brackets_fail)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(2),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(OPEN_BRACKET),
            ExpressionToken(10),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(3)
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));
}
TEST(expression_validation, extra_closed_brackets_fail)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(2),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(OPEN_BRACKET),
            ExpressionToken(10),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(3),
            ExpressionToken(CLOSED_BRACKET),
            ExpressionToken(CLOSED_BRACKET),
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));
}
TEST(expression_validation, empty_brackets)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(OPEN_BRACKET),
            ExpressionToken(CLOSED_BRACKET)
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));
}
// Brackets are necessary. Even though we can omit them in real life
TEST(expression_validation, prefix_function_without_bracket_fail)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(PREFIX_FUNCTION, "sin", nullptr),
            ExpressionToken("x")
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));
}

TEST(expression_validation, bracket_with_operator_fail)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(OPEN_BRACKET),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(10),
            ExpressionToken(CLOSED_BRACKET)
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));
}
TEST(expression_validation, closed_bracket_with_constant_fail)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(10),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(OPEN_BRACKET),
            ExpressionToken(10),
            ExpressionToken('+', nullptr, -1),
            ExpressionToken(10),
            ExpressionToken(CLOSED_BRACKET),
            ExpressionToken(10)
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));

}
TEST(expression_validation, two_operations_fail)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken('+', nullptr, -1),
            ExpressionToken('+', nullptr, -1)
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));
}
TEST(expression_validation, two_constants_fail)
{
    std::vector<ExpressionToken> tokens = {
            ExpressionToken(10),
            ExpressionToken(20)
    };
    EXPECT_FALSE(InfixExpressionValidator::isExpressionValid(tokens));
}

TEST(expression_evaluation, eval_without_variables_and_functions)
{
    std::string input = "2 + 2 * 2";
    EXPECT_NEAR(PostfixExpressionBuilder::buildPostfixException(input).evaluate(),
              6, 0.00000001);
}

TEST(expression_evaluation, divide_by_zero)
{
    EXPECT_ANY_THROW(PostfixExpressionBuilder::buildPostfixException("2/0").evaluate());
}
TEST(expression_evaluation, negative_sqrt)
{
    EXPECT_ANY_THROW(PostfixExpressionBuilder::buildPostfixException("sqrt(-1)").evaluate());
}
TEST(expression_evaluation, variables)
{
    auto expr = PostfixExpressionBuilder::buildPostfixException("a + b * c / d ^ e");
    expr.setVariable("a", 2);
    expr.setVariable("b", 4);
    expr.setVariable("c", 3);
    expr.setVariable("d", 5);
    expr.setVariable("e", 4);
    EXPECT_NEAR(2.0192, expr.evaluate(), 0.000001);

}
TEST(expression_evaluation, big_expression_with_weird_formatting)
{
    auto expr = PostfixExpressionBuilder::buildPostfixException("2+3*6-10 /15 ^(10-4* 2/sin(a) +    sqrt(100))");
    expr.setVariable("a", M_PI_2);
    EXPECT_NEAR(20, expr.evaluate(), 0.000001);
}