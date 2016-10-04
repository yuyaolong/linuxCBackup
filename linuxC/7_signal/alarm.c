/*************************************************************************
    > File Name: alarm.c
    > Author: yuyaolong
    > Mail: yaolony@g.clemson.edu 
    > Created Time: Thu 14 Jan 2016 12:34:47 AM EST
 ************************************************************************/

#include<stdio.h>

int main()
{
	int counter;
	alarm(1);
	for(counter=0; 1; ++counter)
	{
		printf("counter=%d\n", counter);
	}
	return 0;

}
