#ifndef VIPER_INSTRUCTION_SUB_HH
#define VIPER_INSTRUCTION_SUB_HH
#include <parsing/node.hh>

namespace Parsing
{
    class SubInst : public Node
    {
    public:
        SubInst(Node* lhs, Node* rhs, Size size);

        ~SubInst();

        void Print(std::ostream& stream) const override;

        void Emit(Codegen::SectionHeader* text) override;

    private:
        Node* _lhs;
        Node* _rhs;
        Size _size;
    };
}

#endif