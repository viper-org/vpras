#include <parsing/instruction/mov.hh>

namespace Parsing
{
    MovInst::MovInst(Node* lhs, Node* rhs, Size size)
        :_lhs(std::move(lhs)), _rhs(std::move(rhs)), _size(size)
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
}