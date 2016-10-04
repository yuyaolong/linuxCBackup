#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/stat.h>
int main(int argc, char const *argv[])
{
	if (argc < 3)
	{	
		printf("./mychmod mode filename\n");
		exit(1);
	}

	if (access(argv[2], F_OK)<0)
	{
		perror(argv[2]);
		exit(1);	
	}	

	int mode = atoi(argv[1]);
	int mode8 = 0;
	int tmp[3];
	for(int i=0; i<3; ++i)
	{
		tmp[i] = mode %10;
		mode /= 10;
	}

	mode8 = 8*8*tmp[2] + 8*tmp[1] + tmp[0];

	chmod(argv[2], mode8);

	return 0;
}