#include <diagnostics.hh>
#include <iostream>

constexpr std::string_view bold = "\x1b[1m";
constexpr std::string_view red  = "\x1b[31m";

constexpr std::string_view defaults = "\x1b[0m";

namespace Diagnostics
{
    std::string_view fileName;

    void FatalError(std::string_view sender, std::string_view message)
    {
        std::cerr << bold << sender << ": " << red << "fatal error: " << defaults << message << "\n";
        std::cerr << "compilation terminated.\n";
        std::exit(1);
    }

    void Error(std::string_view sender, std::string_view message)
    {
        std::cerr << bold << sender << ": " << red << "error: " << defaults << message << "\n";
        std::cerr << "compilation terminated.\n";
        std::exit(1);
    }

    void CompilerError(const unsigned int lineNumber, std::string_view message)
    {
        std::cerr << bold << fileName << ":" << lineNumber << ": " << defaults << message << std::endl;
        
        std::exit(1);
    }

    void setFileName(std::string_view newFileName)
    {
        fileName = newFileName;
    }
}