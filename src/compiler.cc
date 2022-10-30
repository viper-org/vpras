#include <compiler.hh>
#include <lexing/lexer.hh>
#include <parsing/parser.hh>
#include <codegen/elf.hh>
#include <diagnostics.hh>
#include <sstream>

Compiler::Compiler(const std::string& inputFileName)
    :_inputFileName(inputFileName)
{
    _inputHandle = std::ifstream(inputFileName);
    if(!_inputHandle.is_open())
        Diagnostics::FatalError("vpras", inputFileName + ": No such file or directory");
    Diagnostics::setFileName(inputFileName);
}

void Compiler::Compile()
{
    Lexing::Lexer* lexer = new Lexing::Lexer(_inputHandle);

    Parsing::Parser parser(lexer);
    
    Codegen::ELF* elf = new Codegen::ELF();

    // Initialize all the default sections
    std::vector<Codegen::SectionHeader*> sections = {
        elf->CreateSectionHeader("", Codegen::ShType::SHT_NULL, 0x00), // Null header
        elf->CreateSectionHeader(".text", Codegen::ShType::SHT_PROGBITS, Codegen::ShFlags::SHF_ALLOC | Codegen::ShFlags::SHF_EXECINSTR), // .text header
        elf->CreateSectionHeader(".shstrtab", Codegen::ShType::SHT_STRTAB, 0x00), // .shstrtab header
        elf->CreateSectionHeader(".symtab", Codegen::ShType::SHT_SYMTAB, 0x00), // .symtab header
        elf->CreateSectionHeader(".strtab", Codegen::ShType::SHT_STRTAB, 0x00), // .strtab header
    };

    Codegen::SectionHeader*& text = sections[1];
    Codegen::SectionHeader*& shstrtab = sections[2];
    Codegen::SectionHeader*& symtab = sections[3];
    Codegen::SectionHeader*& strtab = sections[4];

    for(Parsing::Node* node : parser.Parse())
    {
        node->Emit(text);
        delete node;
    }
    
    // Initialize the section header string table
    for(Codegen::SectionHeader* shHdr : sections)
    {
        for(char c : shHdr->GetName())
            shstrtab->WriteByte(c);
        shstrtab->WriteByte(0x00);
    }

    // Null symtab entry
    symtab->WriteLong(0x00); // st_name
    symtab->WriteByte(0x00); // st_info
    symtab->WriteByte(0x00); // st_other
    symtab->WriteWord(0x00); // st_shndx
    symtab->WriteQuad(0x00); // st_value
    symtab->WriteQuad(0x00); // st_size

    // File symtab entry
    symtab->WriteLong(0x01); // st_name
    symtab->WriteByte(0x04); // st_info
    symtab->WriteByte(0x00); // st_other
    symtab->WriteWord(0xFFF1); // st_shndx
    symtab->WriteQuad(0x00); // st_value
    symtab->WriteQuad(0x00); // st_size

    // .text symtab entry
    symtab->WriteLong(0x00); // st_name
    symtab->WriteByte(0x03); // st_info
    symtab->WriteByte(0x00); // st_other
    symtab->WriteWord(0x01); // st_shndx
    symtab->WriteQuad(0x00); // st_value
    symtab->WriteQuad(0x00); // st_size

    strtab->WriteByte(0x00);
    for(char c : _inputFileName)
        strtab->WriteByte(c);

    strtab->WriteByte(0x00);

    elf->WriteELFHeader();
    std::ofstream out(_inputFileName + ".o");
    elf->Print(out);

    delete elf;
}