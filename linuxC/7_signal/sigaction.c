#include <stdio.h>
#include <signal.h>

void do_sig(int num){
	printf("I am do_sig\n");
	printf("sig = %d\n", num);
}

int main(int argc, char const *argv[])
{
	struct sigaction act;
	act.sa_handler = do_sig;
	//act.sa_handler = SIG_DFL;
	//act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, NULL);//registe action

	while(1){
		printf("***************\n");
		sleep(1);
	}
	return 0;
}