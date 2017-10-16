
#ifndef SIMPLEL_SCANNER_H
#define SIMPLEL_SCANNER_H

#include "token.h"
#include "dictionary.h"
#include <string>
#include <fstream>

namespace lr
{

    class Scanner
    {
    public:

        explicit Scanner(std::string &fileName);

        void    next();

        Token   getToken();

    private:

        void getNextChar();

        char peekChar();

        void addBuffer(char ch);

        void reduceBuffer();

        void preprocess();

        void handleIdentifier();

        void handleString();

        void handleNumber();

        void handleRemark();

        void handleOperation();

        void handleEndOfFile();

        TokenLocation makeTokenLocation();

        void makeToken(TokenType type, TokenValue value, std::string tokStr, int precedence, TokenLocation &location);

    public:

        enum class State
        {
            NONE,
            STRING,
            NUMBER,
            IDENTIFIER,
            END_OF_FILE,
            OPERATION
        };

    private:
        int             line_;
        int             column_;
        char            currentChar_;
        State           state_;
        Token           currentToken_;
        TokenLocation   tokenLocation_;
        std::ifstream   input_;
        std::string     buffer_;
        std::string     filename_;
        Dictionary      dictionary_;

    };

    inline Token Scanner::getToken() { return currentToken_; }

}


#endif //SIMPLEL_SCANNER_H
