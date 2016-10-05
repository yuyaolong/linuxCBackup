#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mtxA = PTHREAD_MUTEX_INITIALIZER, mtxB = PTHREAD_MUTEX_INITIALIZER;

void* fucA(void *arg) {
	pthread_mutex_lock(&mtxA);
	sleep(1);
	pthread_mutex_lock(&mtxB);
	pthread_mutex_unlock(&mtxB);
	pthread_mutex_unlock(&mtxA);
	return NULL;
}


void* fucB(void *arg) {
	pthread_mutex_lock(&mtxB);
	sleep(1);
	pthread_mutex_lock(&mtxA);
	pthread_mutex_unlock(&mtxA);
	pthread_mutex_unlock(&mtxB);
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t tidA, tidB;
	pthread_create(&tidA, NULL, fucA, NULL);
	pthread_create(&tidB, NULL, fucB, NULL);
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);
	return 0;
}
