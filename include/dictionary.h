
#ifndef SIMPLEL_DICTIONARY_H
#define SIMPLEL_DICTIONARY_H

#include <map>
#include <string>
#include <ostream>
#include "token.h"

namespace cen
{

    class Dictionary
    {
    public:
        Dictionary();

        std::tuple<TokenType, TokenValue, int> lookup(const std::string &name) const;

        bool haveToken(std::string &name) const;

    private:
        void addToken(std::string name, std::tuple<TokenType, TokenValue, int> tokenMate);
    private:
        std::map<std::string, std::tuple<TokenType, TokenValue, int>> dictionary_;
    };
}

#endif //SIMPLEL_DICTIONARY_H
