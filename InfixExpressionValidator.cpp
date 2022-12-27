//
// Created by k17 on 27.12.2022.
//

#include <iostream>
#include <cmath>
#include "ExpressionParser.h"
#include "TStack.h"
#include "PostfixExpressionBuilder.h"
#include <sstream>
#include "InfixExpressionValidator.h"

bool InfixExpressionValidator::isExpressionValid(const std::vector<ExpressionToken> &infixTokens) {
    int openBrackets = 0;
    for (int i = 0; i+1 < infixTokens.size(); ++i)
    {
        switch(infixTokens[i].getType()) {
            case OPEN_BRACKET:
                switch(infixTokens[i+1].getType())
                {
                    case CONSTANT:
                    case VARIABLE:
                    case PREFIX_FUNCTION:
                    case OPEN_BRACKET:
                        break;
                    default:
                        return false;
                }
                openBrackets++;
                break;
            case CLOSED_BRACKET:
                switch(infixTokens[i+1].getType())
                {
                    case BINARY_OPERATOR:
                    case POSTFIX_FUNCTION:
                    case CLOSED_BRACKET:
                        break;
                    default:
                        return false;
                }
                openBrackets--;
                break;
            case CONSTANT:
            case VARIABLE:
            case POSTFIX_FUNCTION:
                switch(infixTokens[i+1].getType())
                {
                    case CLOSED_BRACKET:
                    case BINARY_OPERATOR:
                    case POSTFIX_FUNCTION:
                        break;
                    default:
                        return false;
                }
                break;
            case PREFIX_FUNCTION:
                if(infixTokens[i+1].getType() != OPEN_BRACKET)
                    return false;
                break;
            case BINARY_OPERATOR:
                switch(infixTokens[i+1].getType())
                {
                    case OPEN_BRACKET:
                    case CONSTANT:
                    case VARIABLE:
                    case PREFIX_FUNCTION:
                        break;
                    default:
                        return false;
                }
                break;
        }
    }
    if(infixTokens.back().getType() == CLOSED_BRACKET)
    {
        openBrackets--;
    }
    if(openBrackets != 0)
        return false;
    return true;
}