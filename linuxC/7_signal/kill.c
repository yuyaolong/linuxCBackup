/*************************************************************************
    > File Name: kill.c
    > Author: yuyaolong
    > Mail: yaolony@g.clemson.edu 
    > Created Time: Wed 13 Jan 2016 11:03:46 PM EST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("./mykill signal pid\n");
		exit(-1);
	}

	if(kill((pid_t)atoi(argv[2]), atoi(argv[1]))<0 ){
		perror("kill");
		exit(1);
	}

	


	return 0;
}
