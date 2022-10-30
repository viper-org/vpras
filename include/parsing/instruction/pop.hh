#ifndef VIPER_INSTRUCTION_POP_HH
#define VIPER_INSTRUCTION_POP_HH
#include <parsing/node.hh>

namespace Parsing
{
    class PopInst : public Node
    {
    public:
        PopInst(Node* operand, Size size);

        ~PopInst();

        void Print(std::ostream& stream) const override;

        void Emit(Codegen::SectionHeader* text) override;

    private:
        Node* _operand;
        Size _size;
    };
}

#endif