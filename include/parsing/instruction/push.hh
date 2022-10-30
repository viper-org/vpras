#ifndef VIPER_INSTRUCTION_PUSH_HH
#define VIPER_INSTRUCTION_PUSH_HH
#include <parsing/node.hh>

namespace Parsing
{
    class PushInst : public Node
    {
    public:
        PushInst(Node* operand, Size size);

        ~PushInst();

        void Print(std::ostream& stream) const override;

        void Emit(Codegen::SectionHeader* text) override;

    private:
        Node* _operand;
        Size _size;
    };
}

#endif