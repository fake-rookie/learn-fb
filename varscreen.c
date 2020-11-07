#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

int main(void)
{
        int fbfd = open("/dev/fb0", O_RDWR);
        if (fbfd == -1) {
                perror("Open Framebuffer device Error: ");
                exit(1);
        }

        struct fb_var_screeninfo varinfo;
        memset(&varinfo, 0, sizeof(struct fb_var_screeninfo));
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &varinfo) == -1) {
                perror("Can not get var screen info: ");
                exit(1);
        }

        close(fbfd);

#define printcolor(color)                                               \
        printf(#color"\t: offset=%u, \tlength=%u, \tmsb_right=%u\n",      \
               varinfo.color.offset, varinfo.color.length, varinfo.color.msb_right)

        printf("xres\t\t=%u \tyres\t\t=%u\n", varinfo.xres, varinfo.yres);
        printf("xoffset\t\t=%u \tyoffset\t\t=%u\n", varinfo.xoffset, varinfo.yoffset);

        printcolor(red);
        printcolor(green);
        printcolor(blue);
        exit(EXIT_SUCCESS);
}