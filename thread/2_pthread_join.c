//pthread_join can join any thread 
//in one process which is not detached 
//waitpid waits only for terminated children
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thr_fn1(void *arg) {  //normal return 
	printf("thread 1 returning\n");
	return (void *)1;
}

void *thr_fn2(void *arg) {  //pthread_exit
	printf("thread 2 exiting\n");
	pthread_exit((void *)2);
}

void *thr_fn3 (void *arg) { //pthread_cancel
	while (1) {
		printf("thread 3 waiting\n");
		sleep(1);
	}
	
}


int main(int argc, char const *argv[])
{
	pthread_t tid;
	void *tret;

	pthread_create(&tid, NULL, thr_fn1, NULL);
	pthread_join(tid, &tret);
	printf("thread 1 exit code %d\n", (int)tret);

	pthread_create(&tid, NULL, thr_fn2, NULL);
	pthread_join(tid, &tret);
	printf("thread 2 exit code %d\n", (int)tret);

	
	pthread_create(&tid, NULL, thr_fn3, NULL);
	sleep(3);
	pthread_cancel(tid);
	pthread_join(tid, &tret);
	printf("thread 3 exit code %d\n", (int)tret);
	printf("PTHREAD_CANCELED code %d\n", (int)PTHREAD_CANCELED);
	return 0;
}