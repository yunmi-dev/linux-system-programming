#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define THREAD_MAIN
#define THREAD_1
#define THREAD_2

#define TRUE 1
#define FALSE 0

void sig_int_handler(int signum) {
	printf("Received a SIGINT signal by thread %ld\n", pthread_self());
	printf("Terminate this process\n");

	exit(0);
}

void *thread1(void *dummy) {

#ifdef THREAD_1
	signal(SIGINT, sig_int_handler);
#endif
	while(TRUE);
	
	return NULL;
}

void *thread2(void *dummy) {

#ifdef THREAD_2
	signal(SIGINT, sig_int_handler);
#endif
	while(TRUE);

	return NULL;
}

int main() {
	pthread_t tid1, tid2;

	if(pthread_create(&tid1, NULL, thread1, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}

	if(pthread_create(&tid2, NULL, thread2, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}

	printf("Create two threads: tid1=%ld, tid2=%ld\n", tid1, tid2);
	printf("Main thread: tid=%ld\n", pthread_self());

#ifdef THREAD_MAIN
	signal(SIGINT, sig_int_handler);
#endif
	
	printf("Press ^c to quit\n");

	while(TRUE) pause();

	return 0;
}