```
➜  chapter12 git:(main) ✗ readelf -a bpf.o
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          616 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         13
  Section header string table index: 12

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000000  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000040
       0000000000000000  0000000000000000  WA       0     0     1
  [ 3] .bss              NOBITS           0000000000000000  00000040
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] prog              PROGBITS         0000000000000000  00000040
       0000000000000006  0000000000000000  AX       0     0     1
  [ 5] license           PROGBITS         0000000000000000  00000046
       0000000000000004  0000000000000000  WA       0     0     1
  [ 6] .comment          PROGBITS         0000000000000000  0000004a
       000000000000002a  0000000000000001  MS       0     0     1
  [ 7] .note.GNU-stack   PROGBITS         0000000000000000  00000074
       0000000000000000  0000000000000000           0     0     1
  [ 8] .eh_frame         PROGBITS         0000000000000000  00000078
       0000000000000030  0000000000000000   A       0     0     8
  [ 9] .rela.eh_frame    RELA             0000000000000000  000001e8
       0000000000000018  0000000000000018   I      10     8     8
  [10] .symtab           SYMTAB           0000000000000000  000000a8
       0000000000000120  0000000000000018          11    10     8
  [11] .strtab           STRTAB           0000000000000000  000001c8
       000000000000001a  0000000000000000           0     0     1
  [12] .shstrtab         STRTAB           0000000000000000  00000200
       0000000000000061  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)

There are no section groups in this file.

There are no program headers in this file.

There is no dynamic section in this file.

Relocation section '.rela.eh_frame' at offset 0x1e8 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000500000002 R_X86_64_PC32     0000000000000000 prog + 0

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.symtab' contains 12 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS bpf.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    2 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 
     9: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
    10: 0000000000000000     6 FUNC    GLOBAL DEFAULT    4 xdp_drop
    11: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    5 __license

No version information found in this file.
```
