#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SIZE 8192

void sys_err(char* str) {
	perror(str);
	exit(-1);
}

int main(int argc, char const *argv[])
{
	clock_t start_t, end_t;
	start_t = clock();
	char buf[SIZE];
	int fd_src, fd_dest, len;
	if (argc < 3) {
		printf("./mycp src dest\n");
		exit(1);
	}

	fd_src = open(argv[1], O_RDONLY);
	if (fd_src < 0) 
		sys_err("src_open");

	fd_dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_dest < 0) 
		sys_err("dest_open");

	while ((len = read(fd_src, buf, sizeof(buf))) > 0) {
		if (write(fd_dest, buf, len) < 0) {
			close(fd_src);
			close(fd_dest);
			sys_err("write_error");
		}
	}
	close(fd_src);
	close(fd_dest);

	end_t = clock();
	printf("copy time: %f\n", (end_t - start_t) * 1.0 / CLOCKS_PER_SEC);

	return 0;
}
