#ifndef VIPER_PARSING_CONSTANT_IMMEDIATE_HH
#define VIPER_PARSING_CONSTANT_IMMEDIATE_HH
#include <parsing/node.hh>

namespace Parsing
{
    class Immediate : public Node
    {
    public:
        Immediate(long long value);

        void Print(std::ostream& stream) const override;

        void Emit(Codegen::SectionHeader* text) override;
    private:
        long long _value;
    };
}

#endif