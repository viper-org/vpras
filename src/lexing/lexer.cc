#include <lexing/lexer.hh>
#include <diagnostics.hh>
#include <unordered_map>
#include <array>

#define TOKEN(type) { Consume(); return Token(TokenType::type, "", _lineNumber); }

namespace Lexing
{
    Lexer::Lexer(std::ifstream& file)
        :_file(file), _lineNumber(1), _current(_file.get())
    {
    }

    char Lexer::Current() const
    {
        return _current;
    }

    char Lexer::Consume()
    {
        _current = _file.get();
        return _current;
    }

    char Lexer::Peek() const
    {
        return _file.peek();
    }

    Token Lexer::NextToken()
    {
        std::unordered_map<std::string_view, TokenType> keywords = {
            { "section", TokenType::Section },
            { "global",  TokenType::Global },
            { "movq",    TokenType::Movq },
            { "ret",     TokenType::Ret },
            { "rax",     TokenType::Register }, // TODO: Add actual register support
        };

        if(std::isalpha(Current()) || Current() == '_' || Current() == '.')
        {
            std::string value = std::string(1, Current());
            
            while(std::isalnum(Peek()) || Peek() == '_' || Peek() == '.')
            {
                Consume();
                value += Current();
            }
            Consume();

            if(auto it = keywords.find(value); it != keywords.end())
                return Token(keywords.find(value)->second, value, _lineNumber);
            
            return Token(TokenType::Identifier, value, _lineNumber);
        }

        if(isdigit(Current()))
        {
            std::string value = std::string(1, Current());

            while(std::isalnum(Peek()) || Peek() == '_')
            {
                Consume();
                value += Current();
            }
            Consume();

            return Token(TokenType::Integer, value, _lineNumber);
        }

        switch(Current())
        {
            case '\n':
                ++_lineNumber;
            case ' ':
            case '\t':
                Consume();
                return NextToken();
            
            case ':':
                TOKEN(Colon);
            case ',':
                TOKEN(Comma);


            case std::ifstream::traits_type::eof():
                return Token(TokenType::Eof, "EOF", _lineNumber);

            
            default:
            {
                using namespace std::literals;
                Diagnostics::Error("vpras", "Junk at end of line, first unrecognized character is"s + Current());
            }
        }
    }
}