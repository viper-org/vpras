#include <compiler.hh>
#include <lexing/lexer.hh>
#include <parsing/parser.hh>
#include <codegen/elf.hh>
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
    
    Codegen::ELF* elf = new Codegen::ELF();

    for(Parsing::Node* node : parser.Parse())
    {
        //node->Emit(elf);
        delete node;
    }

    elf->CreateSectionHeader("\0", Codegen::ShType::SHT_NULL, 0x00);
    elf->WriteELFHeader();
    elf->Print(std::cout);

    delete elf;
}