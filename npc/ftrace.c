#include <sim.h>
#include <elf.h>
#include <ftrace.h>
#include <stdlib.h>
#include <cerrno>

Func *func;
bool ftrace_enable = false;
int funcnum;
Elf64_Ehdr Ehdr;
Elf64_Shdr *Shdr;   // 所有的 Section Header
Elf64_Shdr Shstrh;
Elf64_Shdr Symh, Strh;
char *shstrtab, *strtab;
void init_ftrace(const char *elf_file) {
    FILE* elf_fp = fopen(elf_file, "r");
    int errNum = errno;
    Assert(elf_fp, "Can not open '%s' , reason: %s\n", elf_file, strerror(errNum));
    assert(fseek(elf_fp, 0, SEEK_SET) == 0);
    // Ehdr
    assert(fread(&Ehdr, sizeof(Elf64_Ehdr), 1, elf_fp));
    // Shdr
    Shdr = (Elf64_Shdr*)calloc(Ehdr.e_shnum, sizeof(Elf64_Shdr));
    assert(fseek(elf_fp, Ehdr.e_shoff, SEEK_SET) == 0);
    assert(fread(Shdr, Ehdr.e_shentsize, Ehdr.e_shnum, elf_fp));
    // Shstrh
    Shstrh = Shdr[Ehdr.e_shstrndx];
    // Shstrtab
    shstrtab = (char *)calloc(Shstrh.sh_size, 1);
    assert(fseek(elf_fp, Shstrh.sh_offset, SEEK_SET) == 0);
    assert(fread(shstrtab, Shstrh.sh_size, 1, elf_fp));

    for (int i = 0; i < Ehdr.e_shnum; i++) {
        if (Shdr[i].sh_type == SHT_SYMTAB) {
            Symh = Shdr[i];
        }
        if (Shdr[i].sh_type == SHT_STRTAB) {
            if (memcmp(shstrtab+Shdr[i].sh_name, ".strtab", 7) == 0) {
                Strh = Shdr[i];
            }
        }
    }

    strtab = (char *)calloc(Strh.sh_size, 1);
    assert(fseek(elf_fp, Strh.sh_offset, SEEK_SET) == 0);
    assert(fread(strtab, Strh.sh_size, 1, elf_fp));
    //Log("strtab:\n");
    for (int cur = 0; cur < Strh.sh_size; ) {
        //Log("%s\n", strtab+cur);
        while (cur < Strh.sh_size && strtab[cur]) cur++;
        if (cur < Strh.sh_size) cur++;
    }
     //找出 symtab 中 类型为 func 的所有项 存到外面去
    int symnum = Symh.sh_size / Symh.sh_entsize;
    funcnum = 0;
    Elf64_Sym symtab[symnum];
    assert(fseek(elf_fp, Symh.sh_offset, SEEK_SET) == 0);
    assert(fread(symtab, Symh.sh_entsize, symnum, elf_fp));
    for (int i = 0; i < symnum; i++) {
        if ((symtab[i].st_info & 0xf) == STT_FUNC) {
            funcnum++;
        }
       // Log("symtab[%d].st_info == %x st_name == %s\n", i, symtab[i].st_info, strtab+symtab[i].st_name);
    }
    Log("myprintf: funcnum = %d\n", funcnum);
    func = (Func*)calloc(funcnum, sizeof(Func));
    funcnum = 0;
    for (int i = 0; i < symnum; i++) {
        if ((symtab[i].st_info&0xf) == STT_FUNC) {
            func[funcnum].name = strtab + symtab[i].st_name;
            if (!func[funcnum].name) func[funcnum].name = "???";
            func[funcnum++].value = symtab[i].st_value;
        }
    }
    for (int i = 0; i < funcnum; i++) {
        Log("myfunc: %s %08x\n", func[i].name, func[i].value);
    }
}

pairpc fstack[MAX_FSTACK];  //ftrace 支持的最大大小栈，默认500000
int ftop;

void ftrace(vaddr_t pc, vaddr_t dnpc, uint32_t instval, vaddr_t ra) {
    //Log("ftrace pc = 0x%08x dnpc = 0x%08x instval = 0x%08x ra = 0x%08x",pc,dnpc,instval,ra);
    if (pc == 0x80000000) {
         for (int i = 0; i < funcnum; i++) {
            if (func[i].value == pc) {
                // for (int j = 0; j < prespace; j++) putchar(' ');
                // prespace += 2;
                fstack[++ftop].dnpc = dnpc;
                fstack[ftop].pc = pc;
                printf("#%d: call: %s at %08x\n", ftop, func[i].name, func[i].value);
            }
        }
    }
    if ((instval & 0b1111111) == 0b1101111) { // jal
        for (int i = 0; i < funcnum; i++) { 
            // 函数调用
            if (func[i].value == dnpc) {
                //for (int j = 0; j < prespace; j++) putchar(' ');
                
                // prespace += 2;
                fstack[++ftop].dnpc = dnpc;
                fstack[ftop].pc = pc;
                printf("#%d: call: %s at %08x\n", ftop, func[i].name, func[i].value);
            }
            // 函数返回：从当前 pc 跳转到 x1（ra）, 且 ra 处值为与栈顶pc+4相等 且栈顶 dnpc 等于 func[i].value
            if (ftop > 0 && dnpc == ra && fstack[ftop].pc + 4 == ra && func[i].value == fstack[ftop].dnpc) {
                // prespace -= 2;
                //for (int j = 0; j < prespace; j++) putchar(' ');
                printf("#%d: ret:  %s at %x to %x\n", ftop, func[i].name, pc, dnpc);
                ftop--;
            }
        }
    }
    if (((instval & 0b111000000000000) == 0) && ((instval & 0b1111111) == 0b1100111)) {
        for (int i = 0; i < funcnum; i++) {
            //call
            if (func[i].value == dnpc) {
                //for (int j = 0; j < prespace; j++) putchar(' ');
                printf("#%d: call: %s at %x\n", ftop, func[i].name, func[i].value);
                // prespace += 2;
            } 
            // ret
            if (ftop > 0 && dnpc == ra && fstack[ftop].pc + 4 == ra && func[i].value == fstack[ftop].dnpc) {
                // prespace -= 2;
                //for (int j = 0; j < prespace; j++) putchar(' ');
                printf("#%d: ret:  %s at %x to %x\n", ftop, func[i].name, pc, dnpc);
                ftop--;
            }
        }
    } 
}

bool ftrace_is_enable(){
    return ftrace_enable;
}

void set_ftrace_enable(){
    printf("Ftrace on\n");
    ftrace_enable = true;
}