/*************************************************************************
    > File Name: pause.c
    > Author: yuyaolong
    > Mail: yaolony@g.clemson.edu 
    > Created Time: Thu 25 Feb 2016 01:32:55 AM EST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

void do_sig(int n){

}

int main(void){
	struct sigaction act;
	act.sa_handler = do_sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);

	pause();
	return 0;
}
