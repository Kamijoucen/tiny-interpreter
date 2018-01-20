
#include "../include/scanner.h"
#include "../include/exception.h"

namespace cen
{
    bool Scanner::errorFlag = false;


    Scanner::Scanner(const std::string &fileName) : currentChar_(0), line_(1), column_(0),
                                                    state_(State::NONE), filename_(fileName)
    {
        input_.open(fileName);
        if (input_.fail()) {
            throw FileAccessError("文件无法访问: " + fileName);
        }
    }

    void Scanner::next()
    {
        bool matched = false;
        do {
            if (state_ != State::NONE)
            {
                matched = true;
            }
            switch (state_)
            {
                case State::NONE:
                    getNextChar();
                    break;
                case State::STRING:
                    handleString();
                    break;
                case State::NUMBER:
                    handleNumber();
                    break;
                case State::IDENTIFIER:
                    handleIdentifier();
                    break;
                case State::OPERATION:
                    handleOperation();
                    break;
                case State::END_OF_FILE:
                    handleEndOfFile();
                    break;
            }
            if (state_ == State::NONE)
            {
                preprocess();
                if (input_.eof())
                {
                    state_ = State::END_OF_FILE;
                }
                else
                {
                    if (std::isalpha(currentChar_))
                    {
                        state_ = State::IDENTIFIER;
                    }
                    else if (std::isdigit(currentChar_))
                    {
                        state_ = State::NUMBER;
                    }
                    else if (currentChar_ == '"')
                    {
                        state_ = State::STRING;
                    }
                    else
                    {
                        state_ = State::OPERATION;
                    }
                }
            }
        } while (!matched);
    }

    void Scanner::getNextChar()
    {
        currentChar_ = static_cast<char>(input_.get());
        if (currentChar_ == '\r' || currentChar_ == '\n')
        {
            ++line_;
            column_ = 0;
        }
        else
        {
            ++column_;
        }
    }

    char Scanner::peekChar()
    {
        return static_cast<char>(input_.peek());
    }

    void Scanner::addBuffer(char ch)
    {
        buffer_.push_back(ch);
    }

    void Scanner::handleIdentifier()
    {
        tokenLocation_ = makeTokenLocation();
        addBuffer(currentChar_);
        getNextChar();
        while (std::isalpha(currentChar_))
        {
            addBuffer(currentChar_);
            getNextChar();
        }
        auto tokenMate = dictionary_.lookup(buffer_);
        makeToken(std::get<0>(tokenMate), std::get<1>(tokenMate), buffer_, std::get<2>(tokenMate), tokenLocation_);
    }

    void Scanner::preprocess()
    {
        do {
            while (std::isspace(currentChar_))
            {
                getNextChar();
            }
            handleRemark();
        } while (std::isspace(currentChar_));
    }

    TokenLocation Scanner::makeTokenLocation()
    {
        return TokenLocation(line_, column_, filename_);
    }

    void Scanner::handleString()
    {
        tokenLocation_ = makeTokenLocation();
        getNextChar(); // eat "
        while (currentChar_ != '"' && !input_.eof())
        {
            addBuffer(currentChar_);
            getNextChar();
        }
        getNextChar(); // eat "
        makeToken(TokenType::UNRESERVED, TokenValue::STRING, buffer_, -1, tokenLocation_);
    }

    void Scanner::handleNumber()
    {
        tokenLocation_ = makeTokenLocation();
        addBuffer(currentChar_);
        getNextChar();
        TokenValue tv = TokenValue::INTEGER;
        while (std::isdigit(currentChar_))
        {
            addBuffer(currentChar_);
            getNextChar();
        }
        // 浮点数
        if (currentChar_ == '.')
        {
            tv = TokenValue::FLOAT;
            addBuffer(currentChar_);
            getNextChar();
            while (std::isdigit(currentChar_))
            {
                addBuffer(currentChar_);
                getNextChar();
            }
        }
        makeToken(TokenType::NUMBER, tv, buffer_, 0, tokenLocation_);
    }

    void
    Scanner::makeToken(TokenType type, TokenValue value, std::string tokStr, int precedence, TokenLocation& tokenLocation)
    {
        state_ = State::NONE;
        buffer_.clear();
        currentToken_ = Token(type, value, std::move(tokStr), tokenLocation, precedence);
    }

    void Scanner::handleRemark()
    {
        if (currentChar_ == '/' && peekChar() == '/')
        {
            getNextChar(); // eat '/'
            getNextChar(); // eat '/'
            while (currentChar_ != '\r' && currentChar_ != '\n' && !input_.eof())
            {
                getNextChar();
            }
        }
    }

    void Scanner::handleOperation()
    {
        tokenLocation_ = makeTokenLocation();
        addBuffer(currentChar_);
        addBuffer(peekChar());

        if (dictionary_.haveToken(buffer_))
        {
            getNextChar();
        }
        else
        {
            reduceBuffer();
        }
        auto tokenMate = dictionary_.lookup(buffer_);
        makeToken(std::get<0>(tokenMate), std::get<1>(tokenMate), buffer_, std::get<2>(tokenMate), tokenLocation_);
        getNextChar();
    }

    void Scanner::handleEndOfFile()
    {
        tokenLocation_ = makeTokenLocation();
        makeToken(TokenType::UNRESERVED, TokenValue::END_OF_FILE, "END_OF_FILE", -1, tokenLocation_);
        input_.close();
    }

    void Scanner::reduceBuffer()
    {
        buffer_.pop_back();
    }

    void Scanner::handleBlockRemark()
    {
        // todo
    }

}

