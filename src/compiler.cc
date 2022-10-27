#include <compiler.hh>
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
    
    std::stringstream buf;
    buf << _inputHandle.rdbuf();
    _contents = buf.str() + '\n';

    _inputHandle.close();
}

void Compiler::Compile()
{
}