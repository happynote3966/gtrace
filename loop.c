#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void){
	int v = 256;
	//int *p = &v;
	int pid = getpid();
	while(1){
		printf("[%d]%d@%p\n",pid,v,&v);
		sleep(1);
	}
	// no return
	return 0;
}
