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

    enum ShFlags
    {
        SHF_WRITE     = 0x01,
        SHF_ALLOC     = 0x02,
        SHF_EXECINSTR = 0x04,
    };

    class SectionHeader
    {
    public:
        SectionHeader(std::string name, ShType type, unsigned long long flags, unsigned int sh_name);

        void WriteByte(unsigned char      data, std::stringstream* stream = nullptr);
        void WriteWord(unsigned short     data, std::stringstream* stream = nullptr);
        void WriteLong(unsigned long      data, std::stringstream* stream = nullptr);
        void WriteQuad(unsigned long long data, std::stringstream* stream = nullptr);

        unsigned long long GetSize() const;
        std::string_view GetName() const;
        
        void SetOffset(unsigned long long sh_offset);

        void PrintHdr(std::ostream& stream);
        void Print(std::ostream& stream);
    private:
        std::stringstream _data;
        std::stringstream _hdr;
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