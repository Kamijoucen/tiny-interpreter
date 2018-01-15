
#ifndef LLANGUAGE_TEST_H
#define LLANGUAGE_TEST_H

#include <iostream>
#include "../include/token.h"

namespace lr {

    inline std::ostream &operator<<(std::ostream &io, const lr::TokenValue &tokenValue) {
        std::string value = "unkonw token value!";
        using lr::TokenValue;
        switch (tokenValue) {
            case lr::TokenValue::VAR:
                value = "VAR";
                break;
            case lr::TokenValue::DEF:
                value = "DEF";
                break;
            case lr::TokenValue::IF:
                value = "IF";
                break;
            case lr::TokenValue::DO:
                value = "DO";
                break;
            case lr::TokenValue::FOR:
                value = "FOR";
                break;
            case lr::TokenValue::WHILE:
                value = "WHILE";
                break;
            case lr::TokenValue::ELSE:
                value = "ELSE";
                break;
            case lr::TokenValue::RETURN:
                value = "RETURN";
                break;
            case lr::TokenValue::LEFT_PAREN:
                value = "LEFT_PAREN";
                break;
            case lr::TokenValue::RIGHT_PAREN:
                value = "RIGHT_PAREN";
                break;
            case lr::TokenValue::ASSIGN:
                value = "ASSIGN";
                break;
            case lr::TokenValue::IDENTIFIER:
                value = "IDENTIFIER";
                break;
            case lr::TokenValue::ADD:
                value = "ADD";
                break;
            case lr::TokenValue::MINUS:
                value = "MINUS";
                break;
            case lr::TokenValue::MULTIPLY:
                value = "MULTIPLY";
                break;
            case lr::TokenValue::DIVIDE:
                value = "DIVIDE";
                break;
            case lr::TokenValue::AND:
                value = "AND";
                break;
            case lr::TokenValue::OR:
                value = "OR";
                break;
            case lr::TokenValue::NOT:
                value = "NOT";
                break;
            case lr::TokenValue::EQUAL:
                value = "EQUAL";
                break;
            case lr::TokenValue::GREATER_OR_EQUAL:
                value = "GREATER_OR_EQUAL";
                break;
            case lr::TokenValue::LESS_OR_EQUAL:
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
        }
        std::cout << value;
        return io;
    }

    inline std::ostream &operator<<(std::ostream &io, const lr::TokenType &tokenType) {
        std::string type;
        switch (tokenType) {
            case lr::TokenType::DELIMITER:
                type = "DELIMITER";
                break;
            case lr::TokenType::KEYWORDS:
                type = "KEYWORDS";
                break;
            case lr::TokenType::UNRESERVED:
                type = "UNRESERVED";
                break;
            case lr::TokenType::OPERATORS:
                type = "OPERATORS";
                break;
            case lr::TokenType::NUMBER:
                type = "NUMBER";
                break;
            case lr::TokenType::UNKNOWN:
                type = "UNKNOWN";
                break;
        }
        std::cout << type;
        return io;
    }
}


#endif //LLANGUAGE_TEST_H
