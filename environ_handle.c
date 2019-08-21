#include <stdio.h>
#include <stdlib.h>

#include "environ_handle.h"

gtrace_Environ gtrace_environ[] ={
	{"GTRACE_LOG",env_log_handle},
	{NULL,NULL},
};

void environ_handle(void){
	gtrace_Environ *env;
	char *val;
	int i;

	i = 0;
	env = &gtrace_environ[i];
	while(env->environ != NULL){
		val = getenv(env->environ);
		
		if(val){
			env->func(val);
		}
		env = &gtrace_environ[++i];

	}
}

void env_log_handle(char *val){
	puts(val);
}
