#include <stdio.h>
#include <bfd.h>

#include "gtrace_global.h"
#include "elf_analyze.h"

void elf_analyze_init(void){

	bfd_init();
	
	pbfd = bfd_openr(gtrace_global.fname,NULL);

	if(pbfd == NULL){
		puts("bfd_openr");
	}

	bfd_check_format(pbfd,bfd_object);

	printf("%d\n",bfd_get_arch(pbfd));
}
