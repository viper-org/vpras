#include <parsing/parser.hh>
#include <diagnostics.hh>

namespace Parsing
{
    Parser::Parser(Lexing::Lexer* lexer)
        :_lexer(std::move(lexer)), _current(_lexer->NextToken())
    {
    }

    Parser::~Parser()
    {
        delete _lexer;
    }

    Lexing::Token Parser::Current()
    {
        return _current;
    }
    Lexing::Token Parser::Consume()
    {
        _current = _lexer->NextToken();
        return _current;
    }

    void Parser::ExpectToken(Lexing::TokenType type)
    {
        if(Current().GetType() != type)
        {
            Lexing::Token temp(type, "", 0);
            Diagnostics::CompilerError(Current().GetLine(), "Expected " + temp.TypeAsString() + ", found " + Current().TypeAsString());
        }
    }

    std::vector<Node*> Parser::Parse()
    {
        std::vector<Node*> nodes;
        while(Current().GetType() != Lexing::TokenType::Eof)
            nodes.push_back(std::move(ParseTopLevel()));
        
        return nodes;
    }

    Node* Parser::ParseTopLevel()
    {
        switch(Current().GetType())
        {
            case Lexing::TokenType::Movq:
                return ParseMov();
            case Lexing::TokenType::Ret:
                return ParseRet();
            case Lexing::TokenType::Global:
                return ParseLabel();
            default:
                Diagnostics::CompilerError(Current().GetLine(), "Expected top-level directive/instruction, found " + Current().TypeAsString());
        }
    }

    Node* Parser::ParseMov()
    {
        Size size;
        switch(Consume().GetType())
        {
            case Lexing::TokenType::Movq:
                size = Size::QUAD;
                break;

            default:
                return nullptr; // To make the compiler happy
        }

        Node* param1 = ParseParam();

        ExpectToken(Lexing::TokenType::Comma);

        Node* param2 = ParseParam();

        return new MovInst(std::move(param1), std::move(param2), size);
    }

    Node* Parser::ParseRet()
    {
        Consume();

        return new RetInst();
    }


    Node* Parser::ParseLabel()
    {
        Consume(); // Consume the global keyword

        ExpectToken(Lexing::TokenType::Identifier);
        std::string text = Consume().GetText();
        
        ExpectToken(Lexing::TokenType::Colon);
        Consume();

        return new Label(std::move(text));
    }


    Node* Parser::ParseParam()
    {
        switch(Current().GetType())
        {
            case Lexing::TokenType::Register:
                return ParseRegister();
            
            default:
                Diagnostics::CompilerError(Current().GetLine(), "Expected instruction parameter, found " + Current().GetText());
        }
    }

    Node* Parser::ParseRegister()
    {
        return new Register(Consume().GetText(), Size::QUAD);
    }
}