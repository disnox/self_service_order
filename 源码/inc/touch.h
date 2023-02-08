/*
************************************************************************
* file name: include/touch.h
* author: 苏尚宇
* date: Tue Dec 20 10:39:33 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _TOUCH_H__
#define _TOUCH_H__

#include <linux/input.h>

#define TOUCH_DEV	"/dev/input/event0"

extern int touch_init(void);
extern void touch_close(int fd);
extern void get_touch(int touch_fd, int *x, int *y);
extern void get_xy(int touch_fd, int *x, int *y);

#endif
