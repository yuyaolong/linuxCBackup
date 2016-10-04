#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/fb.h>
int main(int argc, char const *argv[])
{
	int fd;
	struct fb_var_screeninfo fb_info;
	fd = open("/dev/fb0", O_RDONLY);
	if(fd < 0)
	{
		perror("open /dev/fb0");
		exit(1);
	}
	ioctl(fd, FBIOGET_VSCREENINFO, &fb_info);
	printf("R=%d\nC=%d\n", fb_info.xres, fb_info.yres);
	close(fd);
	return 0;
}
