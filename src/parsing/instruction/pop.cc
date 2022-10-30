#include <parsing/instruction/pop.hh>
#include <parsing/constant/register.hh>

namespace Parsing
{
    PopInst::PopInst(Node* operand, Size size)
        :Node(NodeType::Instruction), _operand(std::move(operand)), _size(size)
    {
    }

    PopInst::~PopInst()
    {
        delete _operand;
    }

    void PopInst::Print(std::ostream& stream) const
    {
        stream << "<Pop>:\n\t";
        _operand->Print(stream);
    }

    void PopInst::Emit(Codegen::SectionHeader* text)
    {
        if(Register* reg = dynamic_cast<Register*>(_operand))
            text->WriteByte(0x58 + reg->GetID());
    }
}