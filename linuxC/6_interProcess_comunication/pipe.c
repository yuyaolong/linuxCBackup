#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <error.h>
int main(int argc, char const *argv[])
{
	int fd[2];
	pid_t pid;
	char str[1024] = "hello, itcast";
	char buf[1024];
	if(pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}

	pid = fork();
	//father W, child R
	if (pid > 0)
	{
		//in father, close FR
		//fd[0]=Read, fd[1]=wirte
		close(fd[0]);
		sleep(5);
		write(fd[1], str, strlen(str));
		close(fd[1]);
		wait(NULL);
	}
	else if(pid == 0){
		//in child, close CW
		int len, flags;
		close(fd[1]);

		//non block setting
		flags = fcntl(fd[0], F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(fd[0], F_SETFL, flags);

		while(1){
			len = read(fd[0], buf, sizeof(buf));
			//sprintf(str, "child%s", buf);
			if (len == -1)
			{
				if(errno == EAGAIN){
					write(STDOUT_FILENO,"try again\n", 10);
					sleep(1);
						continue;
					}
				else{
					perror("read");
					exit(1);
				}
				
			}
			if (len > 0)
			{
				write(STDOUT_FILENO, buf, len);
				close(fd[0]);
				break;
			}
			if (len == 0)
			{
				close(fd[0]);
				break;
			}
		}
	}
	else
	{
		perror("fork");
		exit(1);
	}



	return 0;
}