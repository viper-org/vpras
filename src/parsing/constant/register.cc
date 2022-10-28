#include <parsing/constant/register.hh>

namespace Parsing
{
    Register::Register(std::string id, Size size)
        :_id(std::move(id)), _size(size)
    {
    }

    void Register::Print(std::ostream& stream) const
    {
        stream << "<Register>: " << _id;
    }
}