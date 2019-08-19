#include "gtrace_global.h"

typedef struct gtrace_Global_{
	unsigned int pid;
	char *fname;
	bool quiet;
}gtrace_Global;

gtrace_Global gtrace_global;
