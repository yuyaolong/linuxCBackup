/*************************************************************************
    > File Name: stat.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Thu 31 Dec 2015 12:51:34 AM EST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
	struct stat s_buff;
	if(argc < 2)
	{
		printf("./app filename\n");
		exit(1);
	}

	if(stat(argv[1], &s_buff)<0)
	{
		perror("stat");
		exit(1);
	}

	printf("%s\t%ld\n", argv[1], s_buff.st_size);

	//usr
	if((s_buff.st_mode & S_IRUSR)  == S_IRUSR)
		printf("r");
	else
		printf("-");
	if((s_buff.st_mode & S_IWUSR)  == S_IWUSR)
		printf("w");
	else
		printf("-");
	if((s_buff.st_mode & S_IXUSR)  == S_IXUSR)
		printf("x");
	else
		printf("-");



	//grp
	if((s_buff.st_mode & S_IRGRP)  == S_IRGRP)
		printf("r");
	else
		printf("-");
	if((s_buff.st_mode & S_IWGRP)  == S_IWGRP)
		printf("w");
	else
		printf("-");
	if((s_buff.st_mode & S_IXGRP)  == S_IXGRP)
		printf("x");
	else
		printf("-");
	
	//oth
	if((s_buff.st_mode & S_IROTH)  == S_IROTH)
		printf("r");
	else
		printf("-");
	if((s_buff.st_mode & S_IWOTH)  == S_IWOTH)
		printf("w");
	else
		printf("-");
	if((s_buff.st_mode & S_IXOTH)  == S_IXOTH)
		printf("x");
	else
		printf("-");

	printf("\n");
	
	
	
	return 0;

}
