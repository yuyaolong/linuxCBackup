#include <stdio.h>

int main(int argc, char const *argv[])
 {
 	extern char **environ;
 	int i;
 	for (int i = 0; environ[i]!=NULL; ++i)
 	{
 		printf("%s\n", environ[i]);
 	}
 	return 0;
 } 