
#include "dictionary.h"

lr::Dictionary::Dictionary()
{
    addToken("def",     std::make_tuple(TokenType::KEYWORDS,     TokenValue::DEF,          -1));
    addToken("var",     std::make_tuple(TokenType::KEYWORDS,     TokenValue::VAR,          -1));
    addToken("if",      std::make_tuple(TokenType::KEYWORDS,     TokenValue::IF,           -1));
    addToken("do",      std::make_tuple(TokenType::KEYWORDS,     TokenValue::DO,           -1));
    addToken("while",   std::make_tuple(TokenType::KEYWORDS,     TokenValue::WHILE,        -1));
    addToken("else",    std::make_tuple(TokenType::KEYWORDS,     TokenValue::ELSE,         -1));

    addToken(";",       std::make_tuple(TokenType::DELIMITER,    TokenValue::SEMICOLON,    -1));

    addToken("=",       std::make_tuple(TokenType::OPERATORS,    TokenValue::ASSIGN,       2));
    addToken("+",       std::make_tuple(TokenType::OPERATORS,    TokenValue::ADD,          10));
    addToken("-",       std::make_tuple(TokenType::OPERATORS,    TokenValue::MINUS,        10));
}

void lr::Dictionary::addToken(std::string name, std::tuple<TokenType, TokenValue, int> tokenMate)
{
    dictionary.insert(std::pair<decltype(name), decltype(tokenMate)>(name, tokenMate));
}

std::tuple<lr::TokenType, lr::TokenValue, int> lr::Dictionary::lookup(std::string &name) const
{
    TokenType   tokenType   = TokenType::IDENTIFIER;
    TokenValue  tokenValue  = TokenValue::UNRESERVED;
    int         precedence  = -1;

    auto result = dictionary.find(name);
    if (result != dictionary.end())
    {
        tokenType   = std::get<0>(result->second);
        tokenValue  = std::get<1>(result->second);
        precedence  = std::get<2>(result->second);
    }
    return std::make_tuple(tokenType, tokenValue, precedence);
}

bool lr::Dictionary::haveToken(std::string &name) const
{
    return dictionary.find(name) != dictionary.end();
}
