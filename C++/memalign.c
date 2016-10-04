#include <stdio.h>

struct A
{
	char a; //1
	int b; //4
	short c; //2
	long long d; //8
	char e; //1
	
};

int main(int argc, char const *argv[])
{
	printf("%d\n", sizeof(short));
	printf("%d\n", sizeof(long));
	printf("%d\n", sizeof(long long));
	printf("%d\n", sizeof(struct A));
	return 0;
}