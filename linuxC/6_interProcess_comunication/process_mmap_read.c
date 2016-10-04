#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
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
	int MAPLEN=0;
	if (argc<2)
	{
		printf("./a.out filename\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	MAPLEN = lseek(fd, 0, SEEK_END);
	if (fd < 0)
	{
		sys_err("open",1);
	}


	mm = mmap(NULL, MAPLEN,  PROT_READ, MAP_SHARED, fd, 0);
	if (mm == MAP_FAILED)
	{
		sys_err("mmap",2);
	}
	close(fd);
	unlink(argv[1]);
	int i=0;
	while(1)
	{
		//sprintf(mm, "read%d\n", i++);
		printf("%d\n", mm->id);
		printf("%s\n", mm->name);
		printf("%c\n", mm->sex);
		sleep(1);
	}

	munmap(mm, MAPLEN);
	return 0;
}

