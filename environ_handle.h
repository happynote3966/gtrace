#ifndef _ENVIRON_HANDLE_H_
#define _ENVIRON_HANDLE_H_

typedef struct gtrace_envriron_{
	char *environ;
	void(*func)(char*);
}gtrace_Environ;

void environ_handle(void);

void env_log_handle(char *val);

#endif
