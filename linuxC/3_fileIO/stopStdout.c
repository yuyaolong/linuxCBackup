/*************************************************************************
    > File Name: stopStdout.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Wed 30 Dec 2015 03:38:49 AM EST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	close(1);
	int fd;
	fd = open("test", O_CREAT|O_TRUNC|O_RDWR, 0666);

	printf("helloworld\n");

}
