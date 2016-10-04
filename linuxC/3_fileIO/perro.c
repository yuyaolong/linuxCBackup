#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	int fd = open("abc", O_WRONLY);
	if(fd<0)
	{
		printf("errno = %d\n", errno);
		printf("yuyaolong: %s\n", strerror(errno));
		//perror("yuyaolong");
	}
	printf("fd = %d\n", fd);
	return 0;
}