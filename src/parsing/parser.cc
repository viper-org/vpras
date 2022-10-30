#include <iostream>
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
        Lexing::Token result = _current;
        _current = _lexer->NextToken();
        return result;
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
        std::cout << Current() << std::endl;
        switch(Current().GetType())
        {
            case Lexing::TokenType::Movq:
                return ParseBinOp<MovInst, Size::QUAD>();
            case Lexing::TokenType::Pushq:
                return ParseUnOp<PushInst, Size::QUAD>();
            case Lexing::TokenType::Popq:
                return ParseUnOp<PopInst, Size::QUAD>();
            case Lexing::TokenType::Subq:
                return ParseBinOp<SubInst, Size::QUAD>();
            case Lexing::TokenType::Ret:
                return ParseZeroOps<RetInst>();
            case Lexing::TokenType::Global:
                return ParseLabel();
            default:
                Diagnostics::CompilerError(Current().GetLine(), "Expected top-level directive/instruction, found " + Current().TypeAsString());
        }
    }


    Node* Parser::ParseLabel()
    {
        Consume(); // Consume the global keyword

        ExpectToken(Lexing::TokenType::Identifier);
        std::string text = Consume().GetText();
        
        ExpectToken(Lexing::TokenType::Colon);
        Consume();

        return new Label(text);
    }


    Node* Parser::ParseParam()
    {
        switch(Current().GetType())
        {
            case Lexing::TokenType::Register:
                return ParseRegister();
            case Lexing::TokenType::Integer:
                return ParseImmediate();
            default:
                Diagnostics::CompilerError(Current().GetLine(), "Expected instruction parameter, found " + Current().TypeAsString());
        }
    }

    Node* Parser::ParseRegister()
    {
        return new Register(Consume().GetText(), Size::QUAD);
    }

    Node* Parser::ParseImmediate()
    {
        std::string text = Consume().GetText();

        return new Immediate(std::stoi(text));
    }
}