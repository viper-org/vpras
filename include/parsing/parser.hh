#ifndef VIPER_PARSING_PARSER_HH
#define VIPER_PARSING_PARSER_HH
#include <parsing/node.hh>
#include <parsing/instruction/mov.hh>
#include <parsing/instruction/push.hh>
#include <parsing/instruction/pop.hh>
#include <parsing/instruction/sub.hh>
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

        template<typename T, Size size>
        Node* ParseBinOp()
        {
            Consume();

            Node* param1 = ParseParam();

            ExpectToken(Lexing::TokenType::Comma);
            Consume();

            Node* param2 = ParseParam();

            return new T(std::move(param1), std::move(param2), size);
        }
        template<typename T, Size size>
        Node* ParseUnOp()
        {
            Consume();

            Node* operand = ParseParam();

            return new T(std::move(operand), size);
        }
        template<typename T>
        Node* ParseZeroOps()
        {
            Consume();
            return new T();
        }

        Node* ParseLabel();

        Node* ParseParam();
        
        Node* ParseRegister();
        Node* ParseImmediate();
    };
}

#endif