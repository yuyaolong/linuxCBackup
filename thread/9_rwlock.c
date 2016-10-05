/* read-write lock: mult read, write wait no one read or write
get the write lock, read lock can not get at this moment until 
write finish
*/
//3个线程不定时写同一全局资源， 5个线程不定时读同一全局资源
//只用写锁退化为互斥锁
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int counter;
pthread_rwlock_t rwlock;

void *th_write(void *arg) {
	int t;
	while (1) {
		pthread_rwlock_wrlock(&rwlock);
		t = counter;
		usleep(100);
		if (counter >= 1000){
			pthread_rwlock_unlock(&rwlock);
			return NULL;
		}
		printf("write %x : counter=%d, ++counter=%d\n", (int)pthread_self(), t, ++counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(100);
	} 
	return NULL;
}

void *th_read(void *arg) {
	while (1) {
		if (counter >= 1000)
			break;
		pthread_rwlock_rdlock(&rwlock);
		printf("read %x : %d\n", (int)pthread_self(), counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(100);
	}
	return NULL;
}


int main(int argc, char const *argv[])
{
	int i;
	pthread_t tid[8];
	pthread_rwlock_init(&rwlock, NULL);
	for (i = 0; i < 3; ++i)
		pthread_create(&tid[i], NULL, th_write, NULL);
	for (i = 0; i < 5; ++i) 
		pthread_create(&tid[i + 3], NULL, th_read, NULL);
	pthread_rwlock_destroy(&rwlock);
	for (i = 0; i < 8; ++i) 
		pthread_join(tid[i], NULL);
	return 0;
}
