#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void sys_err(char *str) {
	perror(str);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int fd;
	struct flock f_lock;
	if (argc < 2) {
		printf("./xx.out filename\n");
		exit(1);
	}

	if ((fd = open(argv[1], O_RDWR)) < 0) 
		sys_err("open");

	//f_lock.l_type = F_WRLCK;
	f_lock.l_type = F_RDLCK;
	f_lock.l_whence = SEEK_SET; // start of a file
	f_lock.l_start = 0;
	f_lock.l_len = 0; // 0 means lock whole file

	fcntl(fd, F_SETLKW, &f_lock);
	printf("get flock\n");
	sleep(3);
	f_lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLKW, &f_lock);
	printf("release flock\n");

	close(fd);
	return 0;
}