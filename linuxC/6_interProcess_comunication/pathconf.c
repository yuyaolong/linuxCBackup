#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fd[2];
	pipe(fd);

	printf("pipe buf: %ld\n", fpathconf(fd[0], _PC_PIPE_BUF));
	return 0;
}