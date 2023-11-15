#include <common.h>
#include <elf.h> 
#define MAX_FSTACK 500000
typedef struct Func_ {
    char *name;
    Elf32_Addr value;
} Func;
typedef struct Pairpc_ {
    vaddr_t pc;
    vaddr_t dnpc;
} pairpc;
void init_ftrace(const char *elf_file);
void ftrace(vaddr_t pc, vaddr_t dnpc, uint32_t instval, uint32_t ra);
bool ftrace_is_enable();
void set_ftrace_enable();