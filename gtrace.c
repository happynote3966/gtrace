#include <stdio.h>
#include <stdlib.h> // EXIT_FAIRURE
#include <string.h> // memset

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
	


int main(int argc, char *argv[], char *envp[]){
	display_logo();

	int i;

	if(argc < 2){
		fprintf(stderr,"%s <args>\n",argv[0]);
		fprintf(stderr,"%s -a <addr> <size> <args>\n",argv[0]);
		return -1;
	}

	for(i = 0; i < argc; i++){
		fprintf(stderr,"[%d] %s\n",i,argv[i]);
	}

	for(i = 0; envp[i] != NULL; i++){
		fprintf(stderr,"[%d] %s\n",i,envp[i]);
	}

	return 0;
}
