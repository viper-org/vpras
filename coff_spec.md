# COFF
## File Header
* Magic number - WORD
* Number of sections - WORD
* Seconds since Unix Epoch - LONG
* Symbol table pointer - LONG
* Number of symbols - LONG
* Size of optional header(unused for object files) - WORD
* Flags - WORD

## Section Header
* Section name - 8 BYTEs or pointer into string table
* Physical address - LONG
* Virtual address - LONG
* Size - LONG
* Offset of section info - LONG
* Offset of relocation info - LONG
* Offset of line number table - LONG
* Number of relocation table entries - WORD
* Number of line table entries - WORD
* Flags - LONG

## 