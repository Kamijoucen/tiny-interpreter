
#include "token.h"

lr::Token::Token(TokenType tokenType, TokenValue tokenValue, std::string strValue,
                 const TokenLocation &tokenLocation) : tokenType_(tokenType), tokenValue_(tokenValue),
                                                       strValue_(std::move(strValue)), tokenLocation_(tokenLocation),
                                                       symbolPrecedence_(-1) {}

lr::Token::Token(TokenType tokenType, TokenValue tokenValue, std::string strValue,
                 const TokenLocation &tokenLocation, int symbolPrecedence) : tokenType_(tokenType),
                                                                             tokenValue_(tokenValue),
                                                                             strValue_(std::move(strValue)),
                                                                             tokenLocation_(tokenLocation),
                                                                             symbolPrecedence_(symbolPrecedence) {}

lr::TokenLocation::TokenLocation(int line, int column, std::string filename)
        : line_(line), column_(column), filename_(std::move(filename)) {}

lr::TokenLocation::TokenLocation(TokenLocation &&location) noexcept : line_(location.line_),
                                                                      column_(location.column_),
                                                                      filename_(std::move(location.filename_)) {}

lr::TokenLocation &lr::TokenLocation::operator=(TokenLocation &&location) noexcept {
    line_ = location.line_;
    column_ = location.column_;
    filename_ = std::move(location.filename_);
    return *this;
}


