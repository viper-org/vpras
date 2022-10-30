#include <lexing/token.hh>

namespace Lexing
{
    Token::Token(TokenType type, const std::string& text, const unsigned int lineNumber)
        :_type(type), _text(text), _lineNumber(lineNumber)
    {
    }

    std::string Token::TypeAsString() const
    {
        switch(_type)
        {
            case TokenType::Colon:
                return "Colon";
            case TokenType::Comma:
                return "Comma";
            case TokenType::Section:
                return "Section";
            case TokenType::Global:
                return "Global";
            case TokenType::Identifier:
                return "Identifier";
            case TokenType::Register:
                return "Register";
            case TokenType::Integer:
                return "Integer";
            case TokenType::Movq:
                return "Movq";
            case TokenType::Pushq:
                return "Pushq";
            case TokenType::Popq:
                return "Popq";
            case TokenType::Subq:
                return "Subq";
            case TokenType::Ret:
                return "Ret";
            case TokenType::Eof:
                return "Eof";
        }
        return ""; // To make the compiler happy
    }

    TokenType Token::GetType() const
    {
        return _type;
    }
    std::string Token::GetText() const
    {
        return _text;
    }
    unsigned int Token::GetLine() const
    {
        return _lineNumber;
    }

    std::ostream& operator<<(std::ostream& stream, Token token)
    {
        stream << "Line " << token.GetLine() << " - " << token.TypeAsString() << "(" << token._text << ")";
        return stream;
    }
}