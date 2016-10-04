#include <stdio.h>

int main(int argc, char const *argv[])
{
	int ch;
	while( (ch = getchar()) != EOF) //ctrl + D
		putchar(toupper(ch));
	return 0;
}