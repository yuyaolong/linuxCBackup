#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
	pid_t pid, pid_c;

	//fork func called once, return twice, 
	//father func return son PID, son func return 0
	pid = fork();
	if (pid > 0)
	{
		while(1){
			printf("I am father %d\n", getpid());
			int reVal;
			pid_c = wait(&reVal);
			printf("wait for child %d\n", pid_c);
			printf("return value %d\n", reVal);
			sleep(1);
		}
	}
	else if(pid == 0)
	{

			printf("I am son %d\n", getpid());

			sleep(3);
	}
	else
	{
		perror("fork");
		exit(1);
	}

	return 0;
}