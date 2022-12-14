#ifndef VIPER_PARSING_CONSTANT_LABEL_HH
#define VIPER_PARSING_CONSTANT_LABEL_HH
#include <parsing/node.hh>

namespace Parsing
{
    class Label : public Node
    {
    public:
        Label(std::string name);

        void Print(std::ostream& stream) const override;

        void Emit(Codegen::SectionHeader* text) override;

        std::string GetName() const;
    private:
        std::string _name;
    };
}

#endif