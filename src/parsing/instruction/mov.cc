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
        if(Register* reg = dynamic_cast<Register*>(_lhs))
        {
            text->WriteByte(0xB8 + reg->GetID());
            _rhs->Emit(text);
        }
    }
}