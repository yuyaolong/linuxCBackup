/*一般情况下,线程终止后,其终止状态一直保留到其它线程调用pthread_join获取它的状态为止。
但是线程也可以被置为detach状态,这样的线程一旦终止就立刻回收 它占用的所有资源,而不保留终止状态。
不能对一个已经处于detach状态的线程调用pthread_join,这样的调用将返回EINVAL。
如果已经对一个线程调用了pthread_detach就不 能再调用pthread_join了。*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define STACKSIZE 0x100000
void *thr_fn(void *arg) {
	int n = 20;
	while (n--) {
		printf("thread count %d\n", n);
		sleep(1);
	}
	return (void *)1;
}

int main(int argc, char const *argv[])
{
	pthread_t tid;	
	void *tret;
	int err;

	pthread_attr_t attr;
	size_t stacksize;
	void *stackaddr;

	pthread_attr_init(&attr);
	

	stackaddr = malloc(STACKSIZE);
	stacksize = STACKSIZE;
	//set stack address & size
	pthread_attr_setstack(&attr, stackaddr, stacksize);

	pthread_attr_getstack(&attr, &stackaddr, &stacksize);
	printf("stackaddr=%p\n", stackaddr);
	printf("stacksize=%x\n", (int)stacksize);

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&tid, &attr, thr_fn, NULL);
	


	while (1) {
		//if thread is detached, join will fail, here will not wait
		err = pthread_join(tid, &tret);
		if (err) {
			fprintf(stderr, "mian thread: %s\n", strerror(err));
			sleep(10);
			pthread_exit((void*)1);
		} else {
			fprintf(stderr, "thread exit code %d\n", (int)tret);
		}
	}

	return 0;
}
