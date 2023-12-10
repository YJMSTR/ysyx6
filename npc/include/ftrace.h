#ifndef __FTRACE_H__
#define __FTRACE_H__

#include <sim.h>
#include <elf.h> 
#define MAX_FSTACK 500000
typedef uint32_t word_t;
typedef word_t vaddr_t;
typedef struct Func_ {
    char *name;
    Elf32_Addr value;
} Func;
typedef struct Pairpc_ {
    word_t pc;
    word_t dnpc;
} pairpc;
void init_ftrace(const char *elf_file);
void ftrace(vaddr_t pc, vaddr_t dnpc, uint32_t instval, uint32_t ra);
bool ftrace_is_enable();
void set_ftrace_enable();

#endif