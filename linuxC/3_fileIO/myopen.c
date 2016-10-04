#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

	int fd;
	if (argc < 2)
	{
		printf("./app filename\n");
		exit(1);
	}
	umask(0);
	//fd = open(argv[1], O_CREAT|O_RDWR|O_EXCL);
	fd = open(argv[1], O_CREAT|O_RDWR, 0777);
	//fd = open(argv[1], O_RDWR|O_TRUNC);
	char buff[] = "itcast";
	write(fd, buff, strlen(buff));
	printf("fd = %d\n", fd);
	
	close(fd);
	
	return 0;
}
