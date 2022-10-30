#ifndef VIPER_TOKEN_HH
#define VIPER_TOKEN_HH
#include <string>
#include <ostream>

namespace Lexing
{
    enum class TokenType
    {
        Colon,
        Comma,


        Section,
        Global,


        Identifier,
        Register,
        Integer,


        Movq,
        Pushq,
        Popq,
        Subq,
        
        Ret,


        Eof,
    };

    class Token
    {
    public:
        Token(TokenType type, const std::string& text, const unsigned int lineNumber);

        std::string TypeAsString() const;

        TokenType GetType() const;
        std::string GetText() const;
        unsigned int GetLine() const;

        friend std::ostream& operator<<(std::ostream& stream, Token token);
    private:
        TokenType _type;
        std::string _text;

        unsigned int _lineNumber;
    };
}

#endif