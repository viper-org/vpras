#include <compiler.hh>
#include <lexing/lexer.hh>
#include <diagnostics.hh>
#include <sstream>
#include <iostream>


Compiler::Compiler(const std::string& inputFileName)
    :_inputFileName(inputFileName)
{
    _inputHandle = std::ifstream(inputFileName);
    if(!_inputHandle.is_open())
        Diagnostics::FatalError("vpras", inputFileName + ": No such file or directory");
    Diagnostics::setFileName(inputFileName);
}

void Compiler::Compile()
{
    Lexing::Lexer lex(_inputHandle);

    Lexing::Token tok = lex.NextToken();
    while(tok.GetType() != Lexing::TokenType::Eof)
    {
        std::cout << tok << std::endl;
        tok = lex.NextToken();
    }
}