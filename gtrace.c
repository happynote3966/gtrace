#include <stdio.h>
#include <stdlib.h> // EXIT_FAIRURE
#include <string.h> // memset
#include <sys/ptrace.h> // ptrace
#include <unistd.h> // execve,fork
#include <errno.h>

#include "option_handle.h"
#include "environ_handle.h"
#include "elf_analyze.h"


#define LOGO_PATH "logo.txt"

void e(char *str){
	fprintf(stderr,"[ERROR] %s\n",str);
	exit(EXIT_FAILURE);
}

void display_logo(void){
	FILE *fp = NULL;
	char buf[100] = {0};

	fp = fopen(LOGO_PATH,"r");
	
	if(fp == NULL){
		e("Can't opne the \"logo.txt\"!");
	}

	while(fgets(buf,sizeof(buf),fp) != NULL){
		printf("%s",buf);
		memset(buf,0x0,sizeof(buf));
	}

	fclose(fp);
}

typedef struct{
	unsigned long start;
	unsigned long end;
	unsigned char perm;
	unsigned long offset;
	unsigned int major;
	unsigned int minor;
	unsigned long inode;
	char *filename;
}MemoryMap;

MemoryMap *maps[100] = {0};

#define PERM_READ 3
#define PERM_WRITE 2
#define PERM_EXEC 1
#define PERM_PRES 0

#define set_read(x) x |= 1 << PERM_READ
#define set_write(x) x |= 1 << PERM_WRITE
#define set_exec(x) x |= 1 << PERM_EXEC
#define set_pres(x) x |= 1 << PERM_PRES

void getmemorymap(int pid){
	char buf[200] = {0};
	char path[20] = {0};
	FILE *fp = NULL;
	unsigned short maps_index = 0;
	sprintf(buf,"%d",pid);
	strcpy(path,"/proc/");
	strcat(path,buf);
	strcat(path,"/maps");

	fp = fopen(path,"r");
	char *p;
	while(fgets(buf,sizeof(buf),fp) != NULL){
		MemoryMap *map = (MemoryMap *)calloc(1,sizeof(MemoryMap));
		map->start = strtol(strtok(buf,"-"),NULL,16);
		map->end = strtol(strtok(NULL," "),NULL,16);
		p = strtok(NULL," ");
		if(p[0] == 'r'){
			set_read(map->perm);
		}
		if(p[1] == 'w'){
			set_write(map->perm);
		}
		if(p[2] == 'x'){
			set_exec(map->perm);
		}
		if(p[3] == 'p'){
			set_pres(map->perm);
		}
		map->offset = strtol(strtok(NULL," "),NULL,16);
		map->major = strtol(strtok(NULL,":"),NULL,16);
		map->minor = strtol(strtok(NULL," "),NULL,16);
		map->inode = strtol(strtok(NULL," "),NULL,10);
		map->filename = strdup(strtok(NULL," "));
		if(strcmp(map->filename,"\n") == 0){
			map->filename = NULL;
		}else{
			char *newline = strchr(map->filename,'\n');
			*newline = '\0';
		}
		printf("%016lx-%016lx PERM[%d] %lx %02x:%02x %ld %s\n",map->start,map->end,map->perm,map->offset,map->major,map->minor,map->inode,map->filename);
		maps[maps_index] = map;
	}
		
}
	

	
void trace(char *argv[], char *envp[]){
    int pid;
    pid = fork();

    if(pid == 0){
        if(ptrace(PTRACE_TRACEME,0,NULL,NULL) != -1){
            execve(argv[1],&argv[1],envp);
        }else{
            e("ptrace traceme failed");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }else if(pid == -1){
        e("fork is failed");
        exit(EXIT_FAILURE);
    }else{
		sleep(1);
		getmemorymap(pid);
        return;
    }
}

int attached_pid = 0;
void attach(int pid){
	if(pid != 0){
		printf("%d",pid);
		if(ptrace(PTRACE_ATTACH,pid,NULL,NULL) != -1){
			attached_pid = pid;
			printf("attach");
		}else{
			printf("%d\n",errno);
			//printf("%s\n",explain_errno_ptrace(errno,PTRACE_ATTACH,pid,NULL,NULL));
		}
	}
}

void detach(){
	if(attached_pid != 0){
		if(ptrace(PTRACE_DETACH,0,NULL,NULL) != -1){
			attached_pid = 0;
		}
	}
}

void cont(){
	if(attached_pid != 0){
		if(ptrace(PTRACE_CONT,attached_pid,NULL,NULL) != -1){
		}
	}
}

void wm(void *addr, unsigned int value){
	if(attached_pid != 0){
		if(ptrace(PTRACE_POKEDATA,attached_pid,addr,value) != -1){
			printf("OK");
		}else{
			printf("NG");
		}
	}
}

int main(int argc, char *argv[]){
	option_handle(argc,argv);
	environ_handle();

	elf_analyze_init();
	elf_analyze_section();
	//display_logo();
	//trace(argv,envp);

	//attach(atoi(argv[1]));
	//wm((void *)strtol(argv[2],NULL,16),0x41414141);
	//cont();
	//detach();

	//if(argc < 2){
	//	fprintf(stderr,"%s <args>\n",argv[0]);
	//	return -1;
	//}


	return 0;
}
