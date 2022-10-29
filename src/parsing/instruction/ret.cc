#include <parsing/instruction/ret.hh>

namespace Parsing
{
    RetInst::RetInst()
        :Node(NodeType::Instruction)
    {
    }

    void RetInst::Print(std::ostream& stream) const
    {
        stream << "<Ret>";
    }

    void RetInst::Emit(Codegen::ELF* elf)
    {
        elf->WriteByte(0xC3);
    }
}