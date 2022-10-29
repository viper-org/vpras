#ifndef VIPER_CODEGEN_ELF_HH
#define VIPER_CODEGEN_ELF_HH
#include <sstream>
#include <ostream>
#include <vector>

namespace Codegen
{
    enum class ShType
    {
        SHT_NULL,
        SHT_PROGBITS,
        SHT_SYMTAB,
        SHT_STRTAB
    };

    enum class ShFlags
    {
        SHF_WRITE     = 0x01,
        SHF_ALLOC     = 0x02,
        SHF_EXECINSTR = 0x04,
    };

    class SectionHeader
    {
    public:
        SectionHeader(std::string name, ShType type, unsigned long long flags, unsigned long long offset, unsigned int sh_name);

        void WriteByte(unsigned char      data);
        void WriteWord(unsigned short     data);
        void WriteLong(unsigned long      data);
        void WriteQuad(unsigned long long data);

        unsigned long long GetSize() const;

        void Print(std::ostream& stream);
    private:
        std::stringstream _data;
        std::string _name;
        ShType _sh_type;
        unsigned long long _sh_flags;
        unsigned long long _sh_offset;
        unsigned int _sh_name;
        unsigned long long _sh_size;
    };

    class ELF
    {
    public:
        ELF();

        void WriteELFHeader();

        SectionHeader* CreateSectionHeader(std::string name, ShType type, unsigned long long flags);

        void WriteByte(unsigned char      data);
        void WriteWord(unsigned short     data);
        void WriteLong(unsigned long      data);
        void WriteQuad(unsigned long long data);

        void WriteBytes(unsigned char data, int n);

        void Print(std::ostream& stream);
    private:
        std::stringstream _out;
        std::vector<SectionHeader*> _sectionHeaders;
    };
}

#endif