/*************************************************************************
    > File Name: tty.c
    > Author: yuyaolong
    > Mail: yuyaolong8@gmail.com 
    > Created Time: 日  3/20 02:34:53 2016
 ************************************************************************/
#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("fd 0: %s\n", ttyname(0));
	printf("fd 1: %s\n", ttyname(1));
	printf("fd 2: %s\n", ttyname(2));

	return 0;
}
