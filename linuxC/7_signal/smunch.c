#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#define smunch(pid, bit_pattern) syscall(331, pid, bit_pattern) 

void sighandler(int arg)
{
	printf("sighandler arg:%d\n", arg);
}

int main(int argc, char *argv[])
{
    sigset_t sigs;
	int ret;
	ret = sigemptyset(&sigs);
	sigaddset(&sigs, SIGKILL);
	//sigaddset(&sigs, SIGCHLD);
	//sigaddset(&sigs, SIGCONT);
	//sigaddset(&sigs, SIGURG);
	//sigaddset(&sigs, SIGWINCH);
//	ret = sigaddset(&sigs, SIGHUP);
	//sigfillset(&sigs);
	
	if(argc<2){
		printf("need pid!\n");
		return 1;
	}
	printf("ret: %d sigs:%x\n", ret ,sigs);
	
	ret = smunch(atoi(argv[1]), 256);
	printf("smunch return: %d\n", ret);
	return 0;
}
