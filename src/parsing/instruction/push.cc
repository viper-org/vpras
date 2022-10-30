#include <parsing/instruction/push.hh>
#include <parsing/constant/register.hh>

namespace Parsing
{
    PushInst::PushInst(Node* operand, Size size)
        :Node(NodeType::Instruction), _operand(std::move(operand)), _size(size)
    {
    }

    PushInst::~PushInst()
    {
        delete _operand;
    }

    void PushInst::Print(std::ostream& stream) const
    {
        stream << "<Push>:\n\t";
        _operand->Print(stream);
    }

    void PushInst::Emit(Codegen::SectionHeader* text)
    {
        if(Register* reg = dynamic_cast<Register*>(_operand))
            text->WriteByte(0x50 + reg->GetID());
        else
        {
            text->WriteByte(0x68);
            _operand->Emit(text);
        }
    }
}