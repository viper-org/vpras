#ifndef VIPER_INSTRUCTION_MOV_HH
#define VIPER_INSTRUCTION_MOV_HH
#include <parsing/node.hh>

namespace Parsing
{
    class MovInst : public Node
    {
    public:
        MovInst(Node* lhs, Node* rhs, Size size);

        ~MovInst();

        void Print(std::ostream& stream) const override;

    private:
        Node* _lhs;
        Node* _rhs;
        Size _size;
    };
}

#endif