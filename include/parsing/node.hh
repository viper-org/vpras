#ifndef VIPER_PARSING_NODE_HH
#define VIPER_PARSING_NODE_HH
#include <codegen/elf.hh>
#include <ostream>

namespace Parsing
{
    enum class Size
    {
        BYTE,
        WORD,
        LONG,
        QUAD,
    };

    enum class NodeType
    {
        Instruction, Directive,

        Label,

        Register, Immediate,
    };

    class Node
    {
    public:
        Node(NodeType type) :_type(type) {  }
        virtual ~Node() {  }

        NodeType GetType() const { return _type; }

        virtual void Print(std::ostream& stream) const = 0;

        virtual void Emit(Codegen::SectionHeader* text) = 0;
    private:
        NodeType _type;
    };
}

#endif