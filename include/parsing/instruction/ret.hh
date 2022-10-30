#ifndef VIPER_INSTRUCTION_RET_HH
#define VIPER_INSTRUCTION_RET_HH
#include <parsing/node.hh>

namespace Parsing
{
    class RetInst : public Node
    {
    public:
        RetInst();

        void Print(std::ostream& stream) const override;

        void Emit(Codegen::SectionHeader* text) override;
    };
}

#endif