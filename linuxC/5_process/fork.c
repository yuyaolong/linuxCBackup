#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
	pid_t pid;

	//fork func called once, return twice, 
	//father func return son PID, son func return 0
	pid = fork();
	if (pid > 0)
	{
		//while(1){
			printf("I am father\n");
			printf("fpid:%d\n", getpid());
			printf("fppid:%d\n", getppid());
			while(1);
			//sleep(3);
		//}
	}
	else if(pid == 0)
	{
		//while(1)
		//{
			printf("I am son\n");
			printf("spid:%d\n", getpid());
			printf("sppid:%d\n", getppid());
			while(1);
			//sleep(3);
		//}
	}
	else
	{
		perror("fork");
		exit(1);
	}

	return 0;
}