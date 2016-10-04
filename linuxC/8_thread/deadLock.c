#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void *doitA(void *arg)
{
	pthread_mutex_lock(&lock1);
		printf("in tidA, get lock1\n");
		pthread_mutex_lock(&lock2);
		pthread_mutex_unlock(&lock2);
	pthread_mutex_unlock(&lock1);
	return NULL;
}

void *doitB(void *arg)
{
	pthread_mutex_lock(&lock2);
	printf("in tidB, get lock2\n");
	pthread_mutex_lock(&lock1);
	pthread_mutex_unlock(&lock1);
	pthread_mutex_unlock(&lock2);
	return NULL;

}

int main(int argc, char const *argv[])
{
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, doitA, NULL);
	pthread_create(&tidB, NULL, doitB, NULL);

	pthread_join(tidA,NULL);
	pthread_join(tidB,NULL);

	return 0;
}



