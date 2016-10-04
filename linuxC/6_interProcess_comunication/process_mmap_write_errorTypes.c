#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#define MAPLEN 0x1000

struct STU
{	
	int id;
	char name[20];
	char sex;
};


void sys_err(char *str, int exitno)
{
	perror(str);
	exit(exitno);
}

int main(int argc, char const *argv[])
{
	struct STU *mm;
	int fd;
	if (argc<2)
	{
		printf("./a.out filename\n");
		exit(1);
	}
	fd = open(argv[1], O_RDWR|O_CREAT, 0777);
	
	if (fd < 0)
	{
		sys_err("open",1);
	}

/* if no lseek and write, it will have Bus error(core dump),
 caus it can't map 4k from disk file*/
	if(lseek(fd, MAPLEN-1, SEEK_SET) < 0)//creat 4k roam
	{
		sys_err("lseek", 3);
	}
	if(write(fd, "\0", 1) < 0)
	{
		sys_err("write", 4);
	}

	mm = mmap(NULL, MAPLEN,  PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (mm == MAP_FAILED)
	{
		sys_err("mmap",2);
	}
	close(fd);
	int i=0;
	while(1)
	{
		mm->id = i;
		sprintf(mm->name, "Yu-%d", i);
		if (i % 2)
			mm->sex = 'm';
		else
			mm->sex = 'f';
		i++;

		sleep(1);
	}

	munmap(mm, MAPLEN);
	return 0;
}

