#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	if(access("abc", F_OK) < 0)
	{
		perror("abc");
		exit(1);
	}

printf("abc is ok\n");

	return 0;
}