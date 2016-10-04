#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter;
pthread_rwlock_t rwlock;


void *th_write(void *arg)
{	
	int t;
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		t = counter;
		printf("write:%x  counter:%d  ++counter:%d\n", 
				(unsigned int)pthread_self(), t, ++counter);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}

	return NULL;
}

void *th_read(void *arg)
{
	while(1){
		pthread_rwlock_rdlock(&rwlock);
		printf("%x  : %d\n", (unsigned int)pthread_self(), 
				counter);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}


	return NULL;
}
int main(int argc, char const *argv[])
{
	int i=0;
	pthread_rwlock_init(&rwlock, NULL);
	pthread_t tid[8];

	for (i = 0; i < 3; ++i)
	{
		pthread_create(&tid[i], NULL, th_write, NULL);
	}
	for (i = 0; i < 5; ++i)
	{
		pthread_create(&tid[i+3], NULL, th_read, NULL);
	}
	for (i = 0; i < 8; ++i)
	{
		pthread_join(tid[i], NULL);
	}



	return 0;
}
