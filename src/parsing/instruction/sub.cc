#include <parsing/instruction/sub.hh>
#include <parsing/constant/register.hh>

namespace Parsing
{
    SubInst::SubInst(Node* lhs, Node* rhs, Size size)
        :Node(NodeType::Instruction), _lhs(std::move(lhs)), _rhs(std::move(rhs)), _size(size)
    {
    }

    SubInst::~SubInst()
    {
        delete _lhs;
        delete _rhs;
    }

    void SubInst::Print(std::ostream& stream) const
    {
        stream << "<Sub>:\n\t";
        _lhs->Print(stream);
        stream << "\n\t";
        _rhs->Print(stream);
    }

    void SubInst::Emit(Codegen::SectionHeader* text)
    {
        if(Register* left = dynamic_cast<Register*>(_lhs))
        {
            if(Register* right = dynamic_cast<Register*>(_rhs))
            {
                text->WriteByte(0x48);
                text->WriteByte(0x29);
                text->WriteByte(0xC0 + left->GetID() + right->GetID() * 8);
            }
            else
            {
                text->WriteByte(0x48);
                text->WriteByte(0x81);
                text->WriteByte(0xE8 + left->GetID());
                _rhs->Emit(text);
            }
        }
    }
}