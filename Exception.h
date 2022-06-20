//
// Created by teich on 15/06/2022.
//

#include <exception>
#include <string>
using std::string;

#ifndef MTMCHKIN_CPP_EXCEPTION_H
#define MTMCHKIN_CPP_EXCEPTION_H

//class Exception : public std::exception{};

class DeckFileNotFound : public std::exception{
    const char* what() const noexcept override {return "Deck File Error: File not found";}
};

class DeckFileFormatError : public std::exception
{
private:
    std::string m_msg;
public:
    DeckFileFormatError(const std::string& on)
            : m_msg(std::string("Deck File Error: File format error in line ") + on)
    {}

    virtual const char* what() const throw()
    {
        return m_msg.c_str();
    }
};

class DeckFileInvalidSize : public std::exception{
    const char* what() const noexcept override {return "Deck File Error: Deck size is invalid";}
};


#endif //MTMCHKIN_CPP_EXCEPTION_H
