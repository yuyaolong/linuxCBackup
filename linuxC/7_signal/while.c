/*************************************************************************
    > File Name: while.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Wed 13 Jan 2016 10:29:00 PM EST
 ************************************************************************/

#include<stdio.h>
int main()
{
	int a=0;
	char *str = "hello";
	int b = 3/0; //float can not be denominator
	*str = "change"; //segment fault, 11: SIGSEGV 
	while(1);
	return 0;

}
