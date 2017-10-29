
#ifndef SIMPLEL_TOKEN_H
#define SIMPLEL_TOKEN_H

#include <string>
#include <utility>
#include <ostream>

namespace lr
{

    class TokenLocation
    {
    public:
        TokenLocation() = default;

        TokenLocation(TokenLocation &&location) noexcept;

        TokenLocation &operator=(TokenLocation &&location) noexcept;

        TokenLocation(const TokenLocation &location) = default;

        TokenLocation &operator=(const TokenLocation &location) = default;

        TokenLocation(int line, int column, std::string filename);

        std::string toString();

    private:
        int         line_;
        int         column_;
        std::string filename_;
    };

    enum class TokenType
    {
        DELIMITER,          // 分隔符
        KEYWORDS,
        OPERATORS,
        UNRESERVED,
        NUMBER,
        UNKNOWN,
    };

    enum class TokenValue
    {
        // keywords
        VAR,
        DEF,
        IF,
        DO,
        FOR,
        WHILE,
        ELSE,
        RETURN,
        CLASS,
        IMPORT,
        FALSE,
        TRUE,

        // symbols
        LEFT_PAREN,         // (
        RIGHT_PAREN,        // )
        ASSIGN,             // =
        ADD,                // +
        MINUS,              // -
        MULTIPLY,           // *
        DIVIDE,             // /
        AND,                // &&
        OR,                 // ||
        NOT,                // !
        EQUAL,              // ==
        GREATER_OR_EQUAL,   // >=
        LESS_OR_EQUAL,      // <=
        GREATER_THAN,       // >
        LESS_THAN,          // <
        NOT_ASSIGN,         // !=

        // delimiter
        SEMICOLON,          // ;
        COMMA,              // ,
        LEFT_SQUARE,        // [
        RIGHT_SQUARE,       // ]
        LEFT_BRACE,         // {
        RIGHT_BRACE,        // }
        PERIOD,             // .

        // number
        FLOAT,
        INTEGER,

        IDENTIFIER,
        END_OF_FILE,
        STRING
    };

    class Token
    {
    public:

        Token() = default;

        Token(TokenType tokenType, TokenValue tokenValue, std::string strValue,
              const TokenLocation &tokenLocation);

        Token(TokenType tokenType, TokenValue tokenValue, std::string strValue,
              const TokenLocation &tokenLocation, int symbolPrecedence);

        TokenType       getTokenType() const;

        TokenValue      getTokenValue() const;

        std::string     getStrValue() const;

        TokenLocation   getTokenLocation() const;

    private:
        TokenType       tokenType_;
        TokenValue      tokenValue_;
        std::string     strValue_;
        TokenLocation   tokenLocation_;
        int             symbolPrecedence_;
    };

    inline TokenType Token::getTokenType() const { return tokenType_; }
    inline TokenValue Token::getTokenValue() const { return tokenValue_; }
    inline std::string Token::getStrValue() const { return strValue_; }
    inline TokenLocation Token::getTokenLocation() const { return tokenLocation_; }

}


#endif //SIMPLEL_TOKEN_H
