#ifndef VIPER_PARSING_CONSTANT_REGISTER_HH
#define VIPER_PARSING_CONSTANT_REGISTER_HH
#include <parsing/node.hh>

namespace Parsing
{
    class Register : public Node
    {
    public:
        Register(std::string id, Size size);

        void Print(std::ostream& stream) const override;

        int GetID() const;

        void Emit(Codegen::SectionHeader* text) override;
    private:
        std::string _id;
        Size _size;
    };
}

#endif