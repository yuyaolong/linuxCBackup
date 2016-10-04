#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NLOOP 5000

int counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
void *doit(void *arg){
	int i, val;
	for (int i = 0; i < NLOOP; ++i)
	{
		pthread_mutex_lock(&counter_mutex);
		val = counter;
		printf("%x: %d\n", (unsigned int)pthread_self(), val+1);
		counter = val + 1;
		pthread_mutex_unlock(&counter_mutex);
		//counter++;
		//printf("%x: %d\n", (unsigned int)pthread_self(), counter);
	}
	return NULL;
}

int main(int argc, char*argv[]){
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, doit, NULL);
	pthread_create(&tidB, NULL, doit, NULL);

	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);

	return 0;
}