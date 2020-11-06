#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

int main(void)
{
        int fbfd;
        fbfd = open("/dev/fb0", O_RDWR);
        if (fbfd == -1) {
                perror("/dev/fb0 open failed: ");
                exit(1);
        }

        struct fb_fix_screeninfo fixinfo;
        memset(&fixinfo, 0, sizeof(struct fb_fix_screeninfo));

        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fixinfo) == -1) {
                perror("Failed to open Fix Screeninfo: ");
                exit(1);
        }

        close(fbfd);

        printf("id     = %s\n", fixinfo.id);
        printf("type   = %u\n", fixinfo.type);
}