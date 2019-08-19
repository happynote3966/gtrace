#include <stdio.h>
#include <unistd.h> // sleep

int main(void){
	while(1){
		sleep(1);
		printf("Hello world!\n");
	}
	return 0;
}
