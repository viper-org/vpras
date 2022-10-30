#include <parsing/instruction/mov.hh>
#include <parsing/constant/register.hh>

namespace Parsing
{
    MovInst::MovInst(Node* lhs, Node* rhs, Size size)
        :Node(NodeType::Instruction), _lhs(std::move(lhs)), _rhs(std::move(rhs)), _size(size)
    {
    }

    MovInst::~MovInst()
    {
        delete _lhs;
        delete _rhs;
    }

    void MovInst::Print(std::ostream& stream) const
    {
        stream << "<Mov>:\n\t";
        _lhs->Print(stream);
        stream << "\n\t";
        _rhs->Print(stream);
    }

    void MovInst::Emit(Codegen::SectionHeader* text)
    {
        if(Register* left = dynamic_cast<Register*>(_lhs))
        {
            if(Register* right = dynamic_cast<Register*>(_rhs))
            {
                text->WriteByte(0x48);
                text->WriteByte(0x89);
                text->WriteByte(0xC0 + left->GetID() + right->GetID() * 8);
            }
            else
            {
                text->WriteByte(0xB8 + left->GetID());
                _rhs->Emit(text);
            }
        }
    }
}