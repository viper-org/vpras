#ifndef VIPER_PARSING_CONSTANT_LABEL_HH
#define VIPER_PARSING_CONSTANT_LABEL_HH
#include <parsing/node.hh>

namespace Parsing
{
    class Label : public Node
    {
    public:
        Label(std::string name);

        void Print(std::ostream& stream) const override;

        void Emit(Codegen::ELF* elf) override;
    private:
        std::string _name;
    };
}

#endif