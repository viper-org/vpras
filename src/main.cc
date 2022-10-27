#include <compiler.hh>
#include <diagnostics.hh>

int main(int argc, char** argv)
{
    if(argc < 2)
        Diagnostics::FatalError("vpras", "no input files");

    Compiler compile = Compiler(argv[1]);
    compile.Compile();

    return 0;
}