//
// Created by k17 on 27.12.2022.
//

#include <iostream>
#include <cmath>
#include "TStack.h"
#include "PostfixExpressionBuilder.h"
#include <sstream>
#include <gmpxx.h>
#include "ExpressionParser.h"

double factorial(int n)
{
    double res = 1.0;
    for(int i = 1; i < n; ++i)
    {
        res *= i+1;
    }
    return res;
}

const std::unordered_map<char, binOperator> ExpressionParser::binaryOperators = {
        {'+', { 1, ([](double a, double b){ return a+b; } ) }},
        {'-', { 1, ([](double a, double b){ return a-b; } ) }},
        {'*', { 2, ([](double a, double b){ return a*b; } ) }},
        {'/', { 2, ([](double a, double b){
            if(b == 0.0) throw std::invalid_argument("You just divided by zero, didn't you?");
            return a/b; } ) }},
        {'^', { 3, ([](double a, double b){ return pow(a, b); } ) }}
};
const std::unordered_map<std::string, unaryFunction> ExpressionParser::unaryFunctions = {
        {"sin", [](double a){return sin(a); }},
        {"cos", [](double a){return cos(a); }},
        {"tg", [](double a){return tan(a); }},
        {"ctg", [](double a){return cos(a)/sin(a); }},
        {"sqrt", [](double a){return sqrt(a);}},
        {"ln", [](double a){return log(a); }}
};
const std::unordered_map<std::string, unaryFunction> ExpressionParser::postfixFunctions = {
        {"!", [](double a){return factorial((int) a); }}
};

void ExpressionParser::ParseTokens(std::stringstream &stream, std::vector<ExpressionToken> &infixTokens,
                                   std::unordered_map<std::string, double> &variables) {
    while((stream >> std::ws).good())
    {
        char c = stream.peek();
        if(binaryOperators.find(c) != binaryOperators.end())
        {
            binOperator op = binaryOperators.at(c);
            infixTokens.emplace_back(c, &op.operation, op.priority);
            stream >> c;
            continue;
        }
        double val;
        if(stream >> val)
        {
           infixTokens.emplace_back(val);
           continue;
        }
        stream.clear(stream.rdstate() & (~std::istream::failbit)); // clear failbit so we can try read again
        std::string funcName;
        int funcNameSize = 0;
        while(stream.good() && funcNameSize < 6) {
            c = stream.peek();
            if((c - '0' >= 0 && c - '0' <= 9) || c == ' ' || c == '(' || c == ')' || c == '\377')
            {
                break;
            }
            else {
                funcName += c;
                stream.seekg(1, std::ios_base::cur);
                ++funcNameSize;
            }
        }
        if(!funcName.empty()) {
            if (unaryFunctions.find(funcName) != unaryFunctions.end()) {
                infixTokens.emplace_back(PREFIX_FUNCTION, funcName, &unaryFunctions.at(funcName));
                continue;
            }
            if (postfixFunctions.find(funcName) != postfixFunctions.end())
            {
                infixTokens.emplace_back(POSTFIX_FUNCTION, funcName, &unaryFunctions.at(funcName));
                continue;
            }
            variables.insert(std::pair<std::string, double>(funcName, std::numeric_limits<double>::quiet_NaN()));
            infixTokens.emplace_back(funcName);
            continue;
        }
        stream << c;
        stream.ignore(1);
        switch(c)
        {
            case '(':
                infixTokens.emplace_back(OPEN_BRACKET);
                break;
            case ')':
                infixTokens.emplace_back(CLOSED_BRACKET);
                break;
            default:
                break;
        }
    }
}