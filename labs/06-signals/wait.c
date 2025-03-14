#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0

void sigchld_handler(int signum) {
	printf("A child killed\n");
	printf("I'm a parent\n");
}

int main() {
	pid_t pid;

	signal(SIGCHLD, sigchld_handler);

	if((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	else if(pid == 0) {
		printf("I'm a child\n");
		sleep(2);
	}
	else {
		while(TRUE);
	}

	return 0;
}