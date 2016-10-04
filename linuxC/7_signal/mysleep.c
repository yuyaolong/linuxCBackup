/*************************************************************************
    > File Name: mysleep.c
    > Author: yuyaolong
    > Mail: yaolony@g.clemson.edu 
    > Created Time: Thu 25 Feb 2016 01:49:29 AM EST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
void do_sig(int n)
{
	

}
int mysleep(int n)
{
	signal(SIGALRM, do_sig);
	alarm(n);//actually, here, when I want to sleep
			 //alarm(1)
			 //-----------> other high priority process use cpu, use more than 1s
			 //				SIGALRM already happen
	pause(); //				now you call paush(), will sleep forever
};

int main(){
	printf("begin\n");
	mysleep(1);
	printf("end\n");
	return (0);

}
