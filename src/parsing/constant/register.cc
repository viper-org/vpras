#include <parsing/constant/register.hh>

namespace Parsing
{
    Register::Register(std::string id, Size size)
        :Node(NodeType::Register), _id(std::move(id)), _size(size)
    {
    }

    void Register::Print(std::ostream& stream) const
    {
        stream << "<Register>: " << _id;
    }

    int Register::GetID() const
    {
        if(_id == "rax")
            return 0;
        if(_id == "rcx")
            return 1;
        if(_id == "rdx")
            return 2;
        if(_id == "rbx")
            return 3;
        if(_id == "rsp")
            return 4;
        if(_id == "rbp")
            return 5;
        if(_id == "rsi")
            return 6;
        if(_id == "rdi")
            return 7;
    }

    void Register::Emit(Codegen::SectionHeader* text)
    {
    }
}