#include <codegen/elf.hh>

namespace Codegen
{
    SectionHeader::SectionHeader(std::string name, ShType sh_type, unsigned long long sh_flags, unsigned int sh_name)
        :_name(std::move(name)), _sh_type(sh_type), _sh_flags(sh_flags), _sh_name(sh_name), _sh_size(0), _sh_info(0)
    {
        if(_sh_type == ShType::SHT_SYMTAB)
            _sh_info = 3;
    }

    void SectionHeader::WriteByte(unsigned char data, std::stringstream* stream)
    {
        std::stringstream& ss = (stream == nullptr)?(_data):(*stream);
        ss.write(reinterpret_cast<const char*>(&data), 1);
        if(!stream)
            _sh_size += 1;
    }
    void SectionHeader::WriteWord(unsigned short data, std::stringstream* stream)
    {
        std::stringstream& ss = (stream == nullptr)?(_data):(*stream);
        ss.write(reinterpret_cast<const char*>(&data), 2);
        if(!stream)
            _sh_size += 2;
    }
    void SectionHeader::WriteLong(unsigned long data, std::stringstream* stream)
    {
        std::stringstream& ss = (stream == nullptr)?(_data):(*stream);
        ss.write(reinterpret_cast<const char*>(&data), 4);
        if(!stream)
            _sh_size += 4;
    }
    void SectionHeader::WriteQuad(unsigned long long data, std::stringstream* stream)
    {
        std::stringstream& ss = (stream == nullptr)?(_data):(*stream);
        ss.write(reinterpret_cast<const char*>(&data), 8);
        if(!stream)
            _sh_size += 8;
    }

    unsigned long long SectionHeader::GetSize() const
    {
        return _sh_size;
    }
    std::string_view SectionHeader::GetName() const
    {
        return _name;
    }

    void SectionHeader::SetOffset(unsigned long long sh_offset)
    {
        _sh_offset = sh_offset;
    }
    void SectionHeader::IncInfo()
    {
        ++_sh_info;
    }

    void SectionHeader::Print(std::ostream& stream)
    {
        size_t size = _data.str().size();
        if(size)
        {
            stream << _data.rdbuf();
            size = ((size + 15) & ~15) - size; // Calculate bytes needed for padding
            while(size--)
            {
                int zero = 0x00;
                stream.write(reinterpret_cast<const char*>(&zero), 1);
            }
        }
    }

    void SectionHeader::PrintHdr(std::ostream& stream)
    {
        WriteLong(_sh_name, &_hdr);
        WriteLong(static_cast<unsigned long>(_sh_type), &_hdr);
        WriteQuad(_sh_flags, &_hdr);
        WriteQuad(0x00, &_hdr); // sh_addr
        if(_sh_type == ShType::SHT_NULL)
            WriteQuad(0x00, &_hdr);
        else
            WriteQuad(_sh_offset, &_hdr);
        WriteQuad(_sh_size, &_hdr);
        if(_sh_type == ShType::SHT_SYMTAB)
            WriteLong(0x04, &_hdr); // sh_link
        else
            WriteLong(0x00, &_hdr); // sh_link
        WriteLong(_sh_info, &_hdr);
        switch(_sh_type) // sh_addralign
        {
            case ShType::SHT_NULL:
                WriteQuad(0x00, &_hdr);
                break;
            case ShType::SHT_PROGBITS:
                WriteQuad(0x10, &_hdr);
                break;
            case ShType::SHT_SYMTAB:
                WriteQuad(0x08, &_hdr);
                break;
            case ShType::SHT_STRTAB:
                WriteQuad(0x01, &_hdr);
                break;
        }
        if(_sh_type == ShType::SHT_SYMTAB)
            WriteQuad(0x18, &_hdr); // sh_entsize
        else
            WriteQuad(0x00, &_hdr); // sh_entsize
        
        stream << _hdr.rdbuf();
    }

    ELF::ELF()
    {
    }

    SectionHeader* ELF::CreateSectionHeader(std::string name, ShType type, unsigned long long flags)
    {
        unsigned long long sh_name = 0;
        for(SectionHeader* shHdr : _sectionHeaders)
            sh_name += shHdr->GetName().size() + 1;

        SectionHeader* shHdr = new SectionHeader(std::move(name), type, flags, sh_name);

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
        unsigned long long total_size = _sectionHeaders.size() * 0x40 + 0x40;
        for(SectionHeader* shHdr : _sectionHeaders)
        {
            total_size = (total_size + 0x0F) & ~0x0F;
            shHdr->SetOffset(total_size);
            total_size += shHdr->GetSize();
            shHdr->PrintHdr(stream);
        }

        for(SectionHeader* shHdr : _sectionHeaders)
        {
            shHdr->Print(stream);
            delete shHdr;
        }
    }
}