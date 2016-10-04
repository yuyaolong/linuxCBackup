#include <stdio.h>
#include <pthread.h>

void *func (void *arg) {
	int *p = (int *)arg;
	printf("process PID = %d\n", getpid());
	printf("child thread ID = %d\n", (unsigned int)pthread_self());
	printf("thread *arg = %d\n", *p);
	sleep(1);
}

int main(int argc, char const *argv[])
{
	pthread_t tid;
	int n = 10;
	int err;
	err = pthread_create(&tid, NULL, func, (void*)&n);
	if (err != 0) {
		fprintf(stderr, "%s\n", strerror(err));
		exit(1);
	}
	printf("process PID = %d\n", getpid());
	printf("main thread ID = %d\n", (unsigned int)pthread_self());
	printf("child thread ID = %d\n", (unsigned int)tid);

	return 0;
}
