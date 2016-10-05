#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h> //open
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

//会创建一个临时文件含有mutex和变量， mmap给两个进程共享， 用mutex控制

struct mt
{
	int num;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutexattr;
};

void sys_err(char *arg) {
	perror(arg);
}

int main(int argc, char const *argv[])
{
	int fd, i, err;
	struct mt *mm;
	pid_t pid;
	fd = open("mt_test", O_CREAT | O_RDWR, 0644);
	//ftruncate 会将参数fd指定的文件大小改为参数length指定的大小。
	ftruncate(fd, sizeof(*mm));

	mm = mmap(NULL, sizeof(*mm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);

	memset(mm, 0, sizeof(*mm));

	pthread_mutexattr_init(&mm->mutexattr);
	//process shared
	pthread_mutexattr_setpshared(&mm->mutexattr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&mm->mutex, &mm->mutexattr);
	pid = fork();//子进程也会有mmap shared映射的空间
	if (pid == 0) {
		for (i = 0; i < 10; ++i) {
			pthread_mutex_lock(&mm->mutex);
			(mm->num)++;
			printf("num+1=: %d\n", mm->num);
			pthread_mutex_unlock(&mm->mutex);
			sleep(1);
		}
	} else if (pid > 0) {
		for (i = 0; i < 10; ++i) {
			pthread_mutex_lock(&mm->mutex);
			mm->num += 2;
			printf("num+2=: %d\n", mm->num);
			pthread_mutex_unlock(&mm->mutex);
			sleep(1);
		}
		wait(NULL);
	}
	err = pthread_mutex_destroy(&mm->mutex);
	if (err)
		sys_err("pthread_mutex_destroy");
	err = pthread_mutexattr_destroy(&mm->mutexattr);
	if (err)
		sys_err("pthread_mutexattr_destroy");
	
	//父子进程都需要释放mmap的地址
	err = munmap(mm, sizeof(*mm));
	if (err)
		sys_err("munmap");

	err = unlink("mt_test"); //两个进程有一个unlink会失败
	if (err)
		sys_err("unlink");
	return 0;
}