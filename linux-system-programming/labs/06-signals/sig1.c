#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

void SigIntHandler(int signum) {
	printf("\nReceived a SIGINT signal\n");
	printf("Terminate this process\n");

	exit(0);
}

int main() {
	signal(SIGINT, SigIntHandler);
	
	while(TRUE) {
		NULL;
	}

	return 0;
}