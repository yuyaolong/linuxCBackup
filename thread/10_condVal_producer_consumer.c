//条件变量给多个线程提供了一个汇合的场所
//生产者消费者模型
/*
pthread_cond_signal (唤醒一个优先级最高的，如果一样就选等待时间最长的)
与
pthread_cond_broadcast (唤醒全部等待的线程)
无需考虑调用线程是否是mutex的拥有者，
也就是所，可以在lock与unlock以外的区域调用。
如果我们对调用行为不关心，那么请在lock区域之外调用吧

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond, 
    pthread_mutex_t *mutex, const struct timespec *abstime);
，一定要在mutex的锁定区域内使用。

条件变量实际上是一个睡眠队列， 必须配合互斥锁使用， 
像内核里的等待队列和spin_lock的搭配
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct msg {
	struct msg *next;
	int num;
};

struct msg *head; //这链表是全局资源，要想操作这个链表，生产者和消费者必须上锁
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER; //条件变量，静态初始化
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p) {
	struct msg *mp;
	for (;;) {
		pthread_mutex_lock(&lock);
		while (head == NULL){
			/*	
				阻塞等待has_product被唤醒
				这个函数在挂起之前，这个函数会先释放互斥量，
				当被唤醒，解除阻塞，返回之前在重新自动获取互斥量
			*/
			pthread_cond_wait(&has_product, &lock); 
		}
		//从头摘除一个节点
		mp = head;
		head = mp->next;
		pthread_mutex_unlock(&lock);
		printf("Consumer %d\n", mp->num);
		free(mp);
		sleep(rand() % 5);
	}
}

void *producer(void *p) {
	struct msg *mp;
	for (;;) {
		mp = malloc(sizeof(struct msg));
		mp->num = rand() % 1000 + 1;
		printf("Produce %d\n", mp->num);
		pthread_mutex_lock(&lock);
		//链表头生产产品
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&has_product);
		sleep(rand() % 5);
	}
}

int main(int argc, char const *argv[])
{
	pthread_t pid, cid;
	srand(time(NULL));
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&cid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	return 0;
}