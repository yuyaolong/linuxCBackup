#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int fd = open("abc", O_RDWR);
	if (fd<0)
	{
		perror("open abc");
		exit(-1);
	}
	// extend a file
	lseek(fd, 0x1000, SEEK_SET);
	write(fd, "a", 1);
	close(fd);

	fd = open("hello", O_RDWR);
	if (fd<0)
	{
		perror("open hello");
		exit(-1);
	}
	// know the size of file
	printf("hello size %d\n", (int)lseek(fd, 0, SEEK_END));
	close(fd);



	return 0;
}