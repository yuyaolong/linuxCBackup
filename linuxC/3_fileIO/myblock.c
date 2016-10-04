#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>


int main(void)
{
	char buf[1024];
	int len;
	len = read(STDIN_FILENO, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, len);
}
