#include <compiler.hh>
#include <lexing/lexer.hh>
#include <parsing/parser.hh>
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
    Lexing::Lexer* lexer = new Lexing::Lexer(_inputHandle);

    Parsing::Parser parser(lexer);

    for(Parsing::Node* node : parser.Parse())
    {
        node->Print(std::cout);
        std::cout << '\n';
        delete node;
    }
}