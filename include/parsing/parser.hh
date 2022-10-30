#ifndef VIPER_PARSING_PARSER_HH
#define VIPER_PARSING_PARSER_HH
#include <parsing/node.hh>
#include <parsing/instruction/mov.hh>
#include <parsing/instruction/push.hh>
#include <parsing/instruction/pop.hh>
#include <parsing/instruction/ret.hh>
#include <parsing/constant/label.hh>
#include <parsing/constant/register.hh>
#include <parsing/constant/immediate.hh>
#include <lexing/lexer.hh>
#include <vector>

namespace Parsing
{
    class Parser
    {
    public:
        Parser(Lexing::Lexer* lexer);

        ~Parser();

        std::vector<Node*> Parse();
    private:
        Lexing::Lexer* _lexer;
        Lexing::Token _current;

        Lexing::Token Current();
        Lexing::Token Consume();

        void ExpectToken(Lexing::TokenType type);

        Node* ParseTopLevel();

        Node* ParseMov();
        Node* ParsePush();
        Node* ParsePop();
        Node* ParseRet();

        Node* ParseLabel();

        Node* ParseParam();
        
        Node* ParseRegister();
        Node* ParseImmediate();
    };
}

#endif