#ifndef VIPER_COMPILER_HH
#define VIPER_COMPILER_HH
#include <string>
#include <fstream>

class Compiler
{
public:
    Compiler(const std::string& inputFileName);

    void Compile();

private:
    std::ifstream _inputHandle;
    std::string _inputFileName;
    std::string _contents;
};

#endif