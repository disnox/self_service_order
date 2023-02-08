/*
************************************************************************
* file name: thread.h
* author: 苏尚宇
* date: Wed Dec 21 14:23:43 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _THREAD_H__
#define _THREAD_H__

extern char obuf[100];

extern void thread_init(void *(*start_routine)(void*), void *restrict arg);
extern void *touch_func(void *arg);
extern void *time_func(void *arg); 

#endif
