
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

    private:
        int         line_;
        int         column_;
        std::string filename_;
    };

    enum class TokenType
    {
        DELIMITER,      // 分隔符
        KEYWORDS,
        IDENTIFIER,
        OPERATORS,
        END_OF_FILE,
        STRING,
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
        ADD,
        MINUS,
        ELSE,

        // symbols
        LEFT_PAREN,     // (
        RIGHT_PAREN,    // )
        ASSIGN,         // =
        UNRESERVED,

        // delimiter
        SEMICOLON,      // ;

        // number
        FLOAT,
        INTEGER
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

        std::string     getStrValue() const ;

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
