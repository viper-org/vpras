#ifndef VIPER_PARSING_NODE_HH
#define VIPER_PARSING_NODE_HH
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

    class Node
    {
    public:
        virtual ~Node() {  }

        virtual void Print(std::ostream& stream) const = 0;
    };
}

#endif