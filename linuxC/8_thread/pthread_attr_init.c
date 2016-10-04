/*************************************************************************
    > File Name: pthread_attr_init.c
    > Author: yuyaolong
    > Mail: yuyaolong8@gmail.com 
    > Created Time: 日  3/20 19:59:59 2016
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
void* th_fun (void * arg){
	int n=10;
	while(n--){
		printf("%x   %d\n", (int)pthread_self(), n);
		sleep(1);
	}
	return (void *)1;
}

int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;
	int err;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&tid, &attr, th_fun, NULL);

	err = pthread_join(tid, NULL);
	while(1){
		if(err !=0 ){
			printf("%s\n", strerror(err));
			pthread_exit((void *)1);
		}
	}


	return 0;
}
