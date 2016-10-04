#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep
#include <pthread.h>
#include <string.h>
#include <sys/types.h> //fstate  open
#include <sys/stat.h> //fstate open
#include <fcntl.h> //open
#include <sys/mman.h> //mmap
#include <time.h> //time_t

int nthread = 5; //THREAD_DEFAULT_COUNT

typedef struct _allocate_task
{
	char *r_mem;
	char *w_mem;
	unsigned long long size;
} allocate_task;

void sys_err(const char* str) {
	perror(str);
	exit(-1);
}

void *thread_copy(void* arg) {
	allocate_task *s = (allocate_task *) arg;
	memcpy(s->w_mem, s->r_mem, s->size);
	return (void *)0;
}


int main(int argc, char const *argv[])
{
	int fdsrc, fddest, err, file_size, task_size, i;
	struct stat sbuf;
	char *psrc, *pdest;
	clock_t start_t, end_t;
	//get start time
	start_t = clock();

	if (argc < 3) {
		printf("%s srcname, destname, nthread\n", argv[0]);
		exit(-1);
	}
	if (argc == 4) {
		nthread = atoi(argv[3]);
	}
	
	if (stat(argv[1], &sbuf) < 0)
			sys_err("stat");
	file_size = sbuf.st_size;
	//dest file open
	//if no one create, read&write, clear file if exist original one
	fddest = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0644); 
	if (fddest < 0)
		sys_err("open");
	// 拓展文件
	if (lseek(fddest, file_size - 1, SEEK_SET) < 0)
		sys_err("lseek");
	// 最后一个字节写入数据，这样才真正拓展
	write(fddest, "\0", 1);

	fdsrc = open(argv[1], O_RDONLY);
	if (fdsrc < 0)
		sys_err("open");

	//dynamical alloc address by mmap
	psrc = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fdsrc, 0);
	if (psrc == MAP_FAILED)
		sys_err("src mmap");
	pdest = mmap(NULL, file_size, PROT_WRITE, MAP_SHARED, fddest, 0);
	if (pdest == MAP_FAILED)
		sys_err("dest mmap");
	close(fdsrc);
	close(fddest);

	allocate_task* workload = malloc(nthread * sizeof(allocate_task));
	task_size = file_size / nthread;

	for (int i = 0; i < nthread; ++i) {
		workload[i].r_mem = psrc + i * task_size;
		workload[i].w_mem = pdest + i * task_size;
		if (i != (nthread - 1) )
			workload[i].size = task_size;
		else
			workload[i].size = file_size - task_size * (nthread - 1);
	}
	
	pthread_t tid[nthread];

	for (int i = 0; i < nthread; ++i) {
		err = pthread_create(&tid[i], NULL, thread_copy, (void *)(&workload[i]));
		if (err) {
			fprintf(stderr, "%s\n", strerror(err));
			break;
		}
	}

	for (int i = 0; i < nthread; ++i)
	{
		pthread_join(tid[i], NULL);
	}
	munmap(psrc, file_size);
	munmap(pdest, file_size);
	free(workload);

	end_t = clock();
	printf("copy use time: %f sec\n", (end_t - start_t) * 1.0 / CLOCKS_PER_SEC);

	return 0;
}



