#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

pthread_t ThreadID[2];

void sig_int_handler(int signum) {
	printf("Received a SIGINT signal by thread %ld\n", pthread_self());
	printf("Terminate other threads: tid=%ld, %ld\n", ThreadID[0], ThreadID[1]);

	for(int i = 0; i < 2; i++) {
		int thread_err_no;
		if(thread_err_no = pthread_cancel(ThreadID[i])) {
			fprintf(stderr, "pthread_cancel error occured, err no: %d\n", thread_err_no);
			exit(1);
		}
	}

	for(int i = 0; i < 2; i++) {
		int thread_err_no;
		if(thread_err_no = pthread_join(ThreadID[i], NULL)) {
			fprintf(stderr, "pthread_join error occured, err no: %d\n", thread_err_no);
			exit(1);
		}
	}

	printf("Threads terminated: tid=%ld, %ld\n", ThreadID[0], ThreadID[1]);

	exit(0);
}

void *thread1(void *dummy) {
	printf("Thread %ld created.....\n", pthread_self());

	if(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}

	if(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)) {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while(TRUE);
}

void *thread2(void *dummy) {
	printf("Thread %ld created.....\n", pthread_self());

	if(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}

	if(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)) {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while(TRUE);
}

int main() {
	if(pthread_create(&ThreadID[0], NULL, thread1, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	if(pthread_create(&ThreadID[1], NULL, thread2, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}

	signal(SIGINT, sig_int_handler);

	printf("Press ^C to quit\n");

	while(TRUE) pause();
	return 0;
}