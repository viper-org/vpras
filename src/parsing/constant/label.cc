#include <parsing/constant/label.hh>

namespace Parsing
{
    Label::Label(std::string name)
        :Node(NodeType::Label), _name(std::move(name))
    {
    }

    void Label::Print(std::ostream& stream) const
    {
        stream << "<Label>: " << _name;
    }

    void Label::Emit(Codegen::SectionHeader* text)
    {
    }
}