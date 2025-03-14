#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>

#define TRUE 1
#define FALSE 0

void my_alarm_handler(int signum) {
	struct passwd *rootptr;

	signal(SIGALRM, my_alarm_handler);
	alarm(1);

	printf("in signal handler\n");

	if((rootptr = getpwnam("root")) == NULL) {
		perror("getpwnam");
		exit(1);
	}

	return;
}

int main() {
	struct passwd *ptr;

	signal(SIGALRM, my_alarm_handler);
	alarm(1);

	while(TRUE) {
		if((ptr = getpwnam("lsp30")) == NULL) {
			perror("getpwnam");
			exit(1);
		}

		if(strcmp(ptr->pw_name, "lsp30") != 0) {
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}

	return 0;
}