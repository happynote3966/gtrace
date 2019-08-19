#ifndef _GTRACE_GLOBAL_H_
#define _GTRACE_GLOBAL_H_

typedef struct gtrace_Global_{
	unsigned int pid;
	char *fname;
	unsigned char quiet;
}gtrace_Global;
gtrace_Global gtrace_global;

#endif
