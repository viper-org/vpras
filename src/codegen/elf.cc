#include <codegen/elf.hh>

namespace Codegen
{
    SectionHeader::SectionHeader(std::string name, ShType sh_type, unsigned long long sh_flags, unsigned long long sh_offset, unsigned int sh_name)
        :_name(std::move(name)), _sh_type(sh_type), _sh_flags(sh_flags), _sh_offset(sh_offset), _sh_name(sh_name), _sh_size(0)
    {
    }

    void SectionHeader::WriteByte(unsigned char data)
    {
        _data.write(reinterpret_cast<const char*>(&data), 1);
        ++_sh_size;
    }
    void SectionHeader::WriteWord(unsigned short data)
    {
        _data.write(reinterpret_cast<const char*>(&data), 2);
        _sh_size += 2;
    }
    void SectionHeader::WriteLong(unsigned long data)
    {
        _data.write(reinterpret_cast<const char*>(&data), 4);
        _sh_size += 4;
    }
    void SectionHeader::WriteQuad(unsigned long long data)
    {
        _data.write(reinterpret_cast<const char*>(&data), 8);
        _sh_size += 8;
    }

    unsigned long long SectionHeader::GetSize() const
    {
        return _sh_size;
    }

    void SectionHeader::Print(std::ostream& stream)
    {
        WriteLong(_sh_name);
        WriteLong(static_cast<unsigned long>(_sh_type));
        WriteQuad(_sh_flags);
        WriteQuad(0x00); // sh_addr
        WriteQuad(_sh_offset);
        WriteQuad(_sh_size);
        if(_sh_type == ShType::SHT_SYMTAB)
        {
            WriteLong(0x04); // sh_link
            WriteLong(0x03); // sh_info
        }
        else
        {
            WriteLong(0x00); // sh_link
            WriteLong(0x00); // sh_info
        }
        switch(_sh_type) // sh_addralign
        {
            case ShType::SHT_NULL:
                WriteQuad(0x00);
                break;
            case ShType::SHT_PROGBITS:
                WriteQuad(0x10);
                break;
            case ShType::SHT_SYMTAB:
                WriteQuad(0x08);
                break;
            case ShType::SHT_STRTAB:
                WriteQuad(1);
                break;
        }
        if(_sh_type == ShType::SHT_SYMTAB)
            WriteQuad(0x12); // sh_entsize
        else
            WriteQuad(0x00); // sh_entsize
        
        stream << _data.rdbuf();
    }

    ELF::ELF()
    {
    }

    SectionHeader* ELF::CreateSectionHeader(std::string name, ShType type, unsigned long long flags)
    {
        unsigned long long _sh_offset = 0;
        for(SectionHeader* shHdr : _sectionHeaders)
        {
            _sh_offset += shHdr->GetSize();
        }
        SectionHeader* shHdr = new SectionHeader(std::move(name), type, flags, _sh_offset, _sectionHeaders.size());

        _sectionHeaders.push_back(shHdr);
        
        return shHdr;
    }

    void ELF::WriteELFHeader()
    {
        // e_ident
        WriteLong(0x464C457F); // ELF Magic
        WriteByte(0x02); // 64-bit
        WriteByte(0x01); // Little-endian
        WriteByte(0x01); // ELF Version
        WriteByte(0x00); // System V ABI
        WriteByte(0x00); // ABI Version, Unused
        WriteBytes(0x00, 7); // Padding

        WriteWord(0x01); // e_type - ET_REL(Relocatable)
        WriteWord(0x3E); // e_machine - AMD x86-64
        WriteLong(0x01); // e_version - 1(Original version of ELF)
        WriteQuad(0x00); // e_entry - 0(Not required for relocatables)

        WriteQuad(0x00); // e_phoff - 0
        WriteQuad(0x40); // e_shoff - 64 bytes into file

        WriteLong(0x00); // e_flags - None

        WriteWord(0x40); // e_ehsize - 64 bytes
        WriteWord(0x00); // e_phentsize - 0 bytes
        WriteWord(0x00); // e_phnum - 0 entries
        
        WriteWord(0x40); // e_shentsize - 64 bytes
        WriteWord(_sectionHeaders.size()); // e_shnum - 5 entries
        WriteWord(0x02); // e_shstrndx - Entry 2
    }

    void ELF::WriteByte(unsigned char data)
    {
        _out.write(reinterpret_cast<const char*>(&data), 1);
    }
    void ELF::WriteWord(unsigned short data)
    {
        _out.write(reinterpret_cast<const char*>(&data), 2);
    }
    void ELF::WriteLong(unsigned long data)
    {
        _out.write(reinterpret_cast<const char*>(&data), 4);
    }
    void ELF::WriteQuad(unsigned long long data)
    {
        _out.write(reinterpret_cast<const char*>(&data), 8);
    }
    void ELF::WriteBytes(unsigned char data, int n)
    {
        while(n--)
            _out.write(reinterpret_cast<const char*>(&data), 1);
    }

    void ELF::Print(std::ostream& stream)
    {
        stream << _out.rdbuf();
        for(SectionHeader* shHdr : _sectionHeaders)
        {
            shHdr->Print(stream);
            delete shHdr;
        }
    }
}