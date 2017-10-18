
#ifndef SIMPLEL_DICTIONARY_H
#define SIMPLEL_DICTIONARY_H

#include <map>
#include <string>
#include <ostream>
#include "token.h"

namespace lr {

    class Dictionary
    {
    public:
        Dictionary();

        std::tuple<TokenType, TokenValue, int> lookup(std::string &name) const;

        std::tuple<TokenType, TokenValue, int> lookup(std::string &&name) const;

        bool haveToken(std::string &name) const;

    private:
        void addToken(std::string name, std::tuple<TokenType, TokenValue, int> tokenMate);
    private:
        std::map<std::string, std::tuple<TokenType, TokenValue, int>> dictionary;
    };
}

#endif //SIMPLEL_DICTIONARY_H
