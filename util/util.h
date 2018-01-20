
#ifndef LLANGUAGE_TEST_H
#define LLANGUAGE_TEST_H

#include <iostream>
#include "../include/token.h"

namespace cen {

    inline std::ostream &operator<<(std::ostream &io, const TokenValue &tokenValue) {
        std::string value = "unkonw token value!";
        switch (tokenValue) {
            case TokenValue::VAR:
                value = "VAR";
                break;
            case TokenValue::DEF:
                value = "DEF";
                break;
            case TokenValue::IF:
                value = "IF";
                break;
            case TokenValue::DO:
                value = "DO";
                break;
            case TokenValue::FOR:
                value = "FOR";
                break;
            case TokenValue::WHILE:
                value = "WHILE";
                break;
            case TokenValue::ELSE:
                value = "ELSE";
                break;
            case TokenValue::RETURN:
                value = "RETURN";
                break;
            case TokenValue::LEFT_PAREN:
                value = "LEFT_PAREN";
                break;
            case TokenValue::RIGHT_PAREN:
                value = "RIGHT_PAREN";
                break;
            case TokenValue::ASSIGN:
                value = "ASSIGN";
                break;
            case cen::TokenValue::IDENTIFIER:
                value = "IDENTIFIER";
                break;
            case TokenValue::ADD:
                value = "ADD";
                break;
            case TokenValue::MINUS:
                value = "MINUS";
                break;
            case TokenValue::MULTIPLY:
                value = "MULTIPLY";
                break;
            case TokenValue::DIVIDE:
                value = "DIVIDE";
                break;
            case TokenValue::AND:
                value = "AND";
                break;
            case TokenValue::OR:
                value = "OR";
                break;
            case TokenValue::NOT:
                value = "NOT";
                break;
            case TokenValue::EQUAL:
                value = "EQUAL";
                break;
            case TokenValue::GREATER_OR_EQUAL:
                value = "GREATER_OR_EQUAL";
                break;
            case TokenValue::LESS_OR_EQUAL:
                value = "LESS_OR_EQUAL";
                break;
            case TokenValue::GREATER_THAN:
                value = "GREATER_THAN";
                break;
            case TokenValue::LESS_THAN:
                value = "LESS_THAN";
                break;
            case TokenValue::SEMICOLON:
                value = "SEMICOLON";
                break;
            case TokenValue::COMMA:
                value = "COMMA";
                break;
            case TokenValue::LEFT_SQUARE:
                value = "LEFT_SQUARE";
                break;
            case TokenValue::RIGHT_SQUARE:
                value = "RIGHT_SQUARE";
                break;
            case TokenValue::LEFT_BRACE:
                value = "LEFT_BRACE";
                break;
            case TokenValue::RIGHT_BRACE:
                value = "RIGHT_BRACE";
                break;
            case TokenValue::PERIOD:
                value = "PERIOD";
                break;
            case TokenValue::FLOAT:
                value = "FLOAT";
                break;
            case TokenValue::INTEGER:
                value = "INTEGER";
                break;
            case TokenValue::CLASS:
                value = "CLASS";
                break;
            case TokenValue::STRING:
                value = "STRING";
                break;
            case TokenValue::END_OF_FILE:
                value = "END_OF_FILE";
                break;
            case TokenValue::PRINT:
                value = "PRINT";
                break;
        }
        std::cout << value;
        return io;
    }

    inline std::ostream &operator<<(std::ostream &io, const TokenType &tokenType) {
        std::string type = "unkonw token type!";
        switch (tokenType) {
            case TokenType::DELIMITER:
                type = "DELIMITER";
                break;
            case TokenType::KEYWORDS:
                type = "KEYWORDS";
                break;
            case TokenType::UNRESERVED:
                type = "UNRESERVED";
                break;
            case TokenType::OPERATORS:
                type = "OPERATORS";
                break;
            case TokenType::NUMBER:
                type = "NUMBER";
                break;
            case TokenType::UNKNOWN:
                type = "UNKNOWN";
                break;
        }
        std::cout << type;
        return io;
    }
}


#endif //LLANGUAGE_TEST_H
