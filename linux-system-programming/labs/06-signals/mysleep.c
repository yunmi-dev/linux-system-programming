#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_alarm_handler(int signum) {
	return;
}

unsigned int mysleep(const unsigned int nsecs) {
	if(nsecs == 0) {
		return 0;
	}

	if(signal(SIGALRM, sig_alarm_handler) == SIG_ERR) {
		return nsecs;
	}

	alarm(nsecs);

	pause();

	return alarm(0);
}

int main() {
	const unsigned int nsecs = 5;

	printf("Wait for %d seconds...\n", nsecs);
	printf("Waited for %u seconds\n", nsecs - mysleep(nsecs));

	return 0;
}