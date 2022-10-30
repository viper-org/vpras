#include <parsing/constant/immediate.hh>

namespace Parsing
{
    Immediate::Immediate(long long value)
        :Node(NodeType::Immediate), _value(value)
    {
    }

    void Immediate::Print(std::ostream& stream) const
    {
        stream << "<Immediate>: " << _value;
    }

    void Immediate::Emit(Codegen::SectionHeader* text)
    {
        text->WriteLong(_value);
    }
}