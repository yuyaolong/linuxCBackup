#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
int main(int argc, char const *argv[])
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		printf("I am parent\n");
		exit(0);
	}
	else if (pid == 0)
	{
		while(1){
			printf("I am %d, my parent is %d\n", getpid(), getppid());
			sleep(3);
		}
	}
	else{
		perror("fork");
		exit(-1);
	}


	return 0;
}