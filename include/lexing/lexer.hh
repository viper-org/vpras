#ifndef VIPER_LEXER_HH
#define VIPER_LEXER_HH
#include <lexing/token.hh>
#include <string>
#include <fstream>

namespace Lexing
{
    class Lexer
    {
    public:
        Lexer(std::ifstream& file);

        Token NextToken();
    private:
        std::ifstream& _file;
        unsigned int _position;
        unsigned int _lineNumber;
        char _current;

        char Current() const;
        char Consume();
        char Peek() const;
    };
}

#endif