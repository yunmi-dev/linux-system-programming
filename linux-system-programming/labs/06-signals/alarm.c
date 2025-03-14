#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

static unsigned int AlarmSecs;

void sig_alarm_handler(int signum) {
	if(signal(signum, sig_alarm_handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	alarm(AlarmSecs);

	putchar('.');

	return;
}

int set_periodic_alarm(unsigned int nsecs) {
	if(signal(SIGALRM, sig_alarm_handler) == SIG_ERR) {
		return -1;
	}

	AlarmSecs = nsecs;

	alarm(nsecs);

	return 0;
}

int main() {
	printf("Doing something every one seconds");

	setbuf(stdout, NULL);


	set_periodic_alarm(1);
	while(TRUE) pause();

	return 0;
}