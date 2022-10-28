#include <parsing/constant/label.hh>

namespace Parsing
{
    Label::Label(std::string name)
        :_name(std::move(name))
    {
    }

    void Label::Print(std::ostream& stream) const
    {
        stream << "<Label>: " << _name;
    }
}