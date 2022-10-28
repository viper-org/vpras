#include <parsing/instruction/ret.hh>

namespace Parsing
{
    RetInst::RetInst()
    {
    }

    void RetInst::Print(std::ostream& stream) const
    {
        stream << "<Ret>";
    }
}