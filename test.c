#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <gelf.h>

int main(void){
	int i,fd;
	Elf *e;
	GElf_Phdr phdr;
	size_t n;

	if(elf_version(EV_CURRENT) == EV_NONE){
		printf("ELF library initialization failed : %s",elf_errmsg(-1));
	}

	if((fd = open("/bin/ls",O_RDONLY,0)) < 0){
		printf("open failed");
	}

	if((e = elf_begin(fd,ELF_C_READ,NULL)) == NULL){
		printf("elf_begin() failed: %s", elf_errmsg(-1));
	}

	if(elf_getphdrnum(e,&n) != 0){
		printf("elf_getphdrnum() failed: %s",elf_errmsg(-1));
	}
	
	for(i = 0; i < n; i++){
		if(gelf_getphdr(e,i,&phdr) != &phdr){
			printf("gelf_getphdr() failed: %s",elf_errmsg(-1));
		}

		printf("%d\n",phdr.p_type);
	}

	
	elf_end(e);
	close(fd);

	return 0;

}
