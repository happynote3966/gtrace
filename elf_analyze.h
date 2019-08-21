#ifndef _ELF_ANALYZE_H_
#define _ELF_ANALYZE_H_

#include <bfd.h>

bfd *pbfd;

void elf_analyze_init(void);

void elf_analyze_section(void);

#endif
