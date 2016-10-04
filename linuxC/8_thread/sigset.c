#include <stdio.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	sigset_t s,p;
	printf("%ld\n", sizeof(s));
	printf("%ld\n", sizeof(sig_atomic_t));	

	return 0;
}
