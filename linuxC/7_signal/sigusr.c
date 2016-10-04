#include <stdio.h>
#include <signal.h>
pid_t sonPid, fatherPid;
static int i=0;
void do_sig_son(int num){
	
	++i; 
	printf("father %d\n",i);
	sleep(1);
	kill(fatherPid, SIGUSR2);
}

void do_sig_father(int num){
	++i; 
	printf("son %d\n", j);
	sleep(1);
	kill(sonPid, SIGUSR1);
}
int main(int argc, char const *argv[])
{
	struct sigaction actSon, actFather;
	actSon.sa_handler = do_sig_son;
	actFather.sa_handler = do_sig_father;
	sigemptyset(&actSon.sa_mask);
	actSon.sa_flags = 0;
	sigemptyset(&actFather.sa_mask);
	actFather.sa_flags = 0;
	sigaction(SIGUSR1, &actSon, NULL);//registe action
	sigaction(SIGUSR2, &actFather, NULL);
	pid_t pid;
	pid = fork();
	if (pid > 0)
	{
		fatherPid = getpid();
		printf("father %d\n", fatherPid);
		
	}
	else
	{
		sonPid = getpid();
		printf("Son %d\n",sonPid);
	}
	kill(sonPid, SIGUSR1);
	// while(1){
	// 	printf("***************\n");
	// 	sleep(1);
	// }
	return 0;
}