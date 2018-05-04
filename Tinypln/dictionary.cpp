
#include "dictionary.h"

namespace cen
{

    Dictionary::Dictionary()
    {
        addToken("def",      std::make_tuple(TokenType::KEYWORDS,     TokenValue::DEF,              -1));
        addToken("var",      std::make_tuple(TokenType::KEYWORDS,     TokenValue::VAR,              -1));
        addToken("if",       std::make_tuple(TokenType::KEYWORDS,     TokenValue::IF,               -1));
        addToken("do",       std::make_tuple(TokenType::KEYWORDS,     TokenValue::DO,               -1));
        addToken("for",      std::make_tuple(TokenType::KEYWORDS,     TokenValue::FOR,              -1));
        addToken("while",    std::make_tuple(TokenType::KEYWORDS,     TokenValue::WHILE,            -1));
        addToken("break",    std::make_tuple(TokenType::KEYWORDS,     TokenValue::BREAK,            -1));
        addToken("continue", std::make_tuple(TokenType::KEYWORDS,     TokenValue::CONTINUE,         -1));
        addToken("else",     std::make_tuple(TokenType::KEYWORDS,     TokenValue::ELSE,             -1));
        addToken("elseif",   std::make_tuple(TokenType::KEYWORDS,     TokenValue::ELSEIF,           -1));
        addToken("return",   std::make_tuple(TokenType::KEYWORDS,     TokenValue::RETURN,           -1));
        addToken("class",    std::make_tuple(TokenType::KEYWORDS,     TokenValue::CLASS,            -1));
        addToken("import",   std::make_tuple(TokenType::KEYWORDS,     TokenValue::IMPORT,           -1));
        addToken("false",    std::make_tuple(TokenType::KEYWORDS,     TokenValue::FALSE,            -1));
        addToken("true",     std::make_tuple(TokenType::KEYWORDS,     TokenValue::TRUE,             -1));
        addToken("print",    std::make_tuple(TokenType::KEYWORDS,     TokenValue::PRINT,            -1));
        addToken("input",    std::make_tuple(TokenType::KEYWORDS,     TokenValue::INPUT,            -1));

        addToken(";",        std::make_tuple(TokenType::DELIMITER,    TokenValue::SEMICOLON,        -1));
        addToken("(",        std::make_tuple(TokenType::DELIMITER,    TokenValue::LEFT_PAREN,       -1));
        addToken(")",        std::make_tuple(TokenType::DELIMITER,    TokenValue::RIGHT_PAREN,      -1));
        addToken(",",        std::make_tuple(TokenType::DELIMITER,    TokenValue::COMMA,            -1));
        addToken("[",        std::make_tuple(TokenType::DELIMITER,    TokenValue::LEFT_SQUARE,      -1));
        addToken("]",        std::make_tuple(TokenType::DELIMITER,    TokenValue::RIGHT_SQUARE,     -1));
        addToken("{",        std::make_tuple(TokenType::DELIMITER,    TokenValue::LEFT_BRACE,       -1));
        addToken("}",        std::make_tuple(TokenType::DELIMITER,    TokenValue::RIGHT_BRACE,      -1));
        addToken(".",        std::make_tuple(TokenType::DELIMITER,    TokenValue::PERIOD,           -1));

        addToken("=",        std::make_tuple(TokenType::OPERATORS,    TokenValue::ASSIGN,           2));
        addToken("+",        std::make_tuple(TokenType::OPERATORS,    TokenValue::ADD,              10));
        addToken("-",        std::make_tuple(TokenType::OPERATORS,    TokenValue::MINUS,            10));
        addToken("*",        std::make_tuple(TokenType::OPERATORS,    TokenValue::MULTIPLY,         20));
        addToken("/",        std::make_tuple(TokenType::OPERATORS,    TokenValue::DIVIDE,           20));
        addToken("&&",       std::make_tuple(TokenType::OPERATORS,    TokenValue::AND,              30));
        addToken("||",       std::make_tuple(TokenType::OPERATORS,    TokenValue::OR,               30));
        addToken("!",        std::make_tuple(TokenType::OPERATORS,    TokenValue::NOT,              40));
        addToken("==",       std::make_tuple(TokenType::OPERATORS,    TokenValue::EQUAL,            2));
        addToken(">=",       std::make_tuple(TokenType::OPERATORS,    TokenValue::GREATER_OR_EQUAL, 2));
        addToken("<=",       std::make_tuple(TokenType::OPERATORS,    TokenValue::LESS_OR_EQUAL,    2));
        addToken(">",        std::make_tuple(TokenType::OPERATORS,    TokenValue::GREATER_THAN,     2));
        addToken("<",        std::make_tuple(TokenType::OPERATORS,    TokenValue::LESS_THAN,        2));
        addToken("!=",       std::make_tuple(TokenType::OPERATORS,    TokenValue::NOT_ASSIGN,       2));
    }

    void Dictionary::addToken(std::string name, std::tuple<TokenType, TokenValue, int> tokenMate)
    {
        dictionary_.insert(std::pair<decltype(name), decltype(tokenMate)>(name, tokenMate));
    }

    std::tuple<TokenType, TokenValue, int> Dictionary::lookup(const std::string &name) const
    {
        TokenType  tokenType  = TokenType::UNRESERVED;
        TokenValue tokenValue = TokenValue::IDENTIFIER;
        int        precedence = -1;

        auto result = dictionary_.find(name);
        if (result != dictionary_.end())
        {
            tokenType  = std::get<0>(result->second);
            tokenValue = std::get<1>(result->second);
            precedence = std::get<2>(result->second);
        }
        return std::make_tuple(tokenType, tokenValue, precedence);
    }

    bool Dictionary::haveToken(const std::string &name) const
    {
        return dictionary_.find(name) != dictionary_.end();
    }
}
