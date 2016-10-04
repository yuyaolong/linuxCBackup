#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define STACKSIZE 0x100000
int print_ntimes(char *arg) {
	sleep(1);
	printf("%s\n", arg);
	return 0;
}
void *th_fun(void *arg) {
	int n = 3;
	while (n--) {
		print_ntimes("thread run\n");		
	}
	return 0;	
}

int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	size_t stacksize = STACKSIZE;
	void *stackaddr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	int i = 1, err;
	while (1) {
		stackaddr = malloc(STACKSIZE);
		pthread_attr_setstack(&attr, stackaddr, stacksize);
		err = pthread_create(&tid, &attr, th_fun, NULL);
		//no thread attr
		//err = pthread_create(&tid, NULL, th_fun, NULL);
		if (err) {
			fprintf(stderr, "%s\n", strerror(err));
			exit(1);
		}
		printf("%d\n", i++);
	}
	return 0;
}
