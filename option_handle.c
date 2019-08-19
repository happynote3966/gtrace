#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h> // getopt_long
#include <string.h> // strdup
#include "option_handle.h"
#include "gtrace_global.h"

const struct option longopts[] = {
	{"filename",required_argument,NULL,'f'},
	{"processid",required_argument,NULL,'p'},
	{"help",no_argument,NULL,'h'},
	{"version",no_argument,NULL,'v'},
	{"quiet",no_argument,NULL,'q'},
	{"log",required_argument,NULL,'l'},
	{0,0,0,0},
};

void option_handle(int argc, char *argv[], char *envp[]){
	int opt;
	int longindex;
	while((opt = getopt_long(argc,argv,"f:p:hvq",longopts,&longindex)) != -1){
		switch(opt){
			case 'f':
				opt_filename_handle(optarg);
				break;
			case 'p':
				opt_processid_handle(optarg);
				break;
			case 'h':
				opt_help_handle();
				break;
			case 'v':
				puts("version");
				break;
			case 'q':
				puts("quiet");
				break;
			case 'l':
				opt_log_handle(optarg);
				break;
			default:
				fprintf(stderr,"Usage: %s [f:p:hvq]\n",argv[0]);
				exit(EXIT_FAILURE);
		}
	}
}

void opt_version_handle(void){
	puts("gtrace version 0.1");
	exit(EXIT_SUCCESS);
}

void opt_help_handle(void){
	puts("help");
	exit(EXIT_SUCCESS);
}

void opt_log_handle(char *logname){
	puts("opt_log_handle");
}

void opt_filename_handle(char *filename){
	puts("opt_filename_handle");

	gtrace_global.fname = strdup(filename);
	puts(gtrace_global.fname);

	puts(filename);
}

void opt_processid_handle(char* processid){
	puts("opt_processid_handle");
	printf("%s\n",processid);
}
