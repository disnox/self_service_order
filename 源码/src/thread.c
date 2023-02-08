/*
************************************************************************
* file name: thread.c
* author: 苏尚???
* date: Wed Dec 21 14:23:37 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "thread.h"
#include "touch.h"
#include "callback.h"
#include "menu_info.h"
#include "control.h"
#include "main.h"
#include "font.h"
#include "display.h"

char obuf[100];
/*
************************************************************************
* @brief      thread_init()
* @param      start_routine: 任务函数名称
*			  arg: 线程参数
* @return     void
* describe:   添加任务
************************************************************************
*/  
void thread_init(void *(*start_routine)(void*), void *restrict arg)
{
	pthread_t thread;
    int ret;
printf("--------------------------\n");
    ret = pthread_create(&thread, NULL, start_routine, arg);
    if (ret != 0) {
        printf("Failed to create thread\n");
        exit(1);
    }
}
/*
************************************************************************
* @brief      touch_func()
* @param      arg: 线程参数
* @return     void
* describe:   触摸事件任务
************************************************************************
*/  
void *touch_func(void *arg)
{
	int touch_fd = touch_init();
printf("--------------------------\n");
	while(1) {
printf("--------------------------\n");
		get_touch(touch_fd, &x, &y);
		printf("(%d,%d)\n", x, y);
		// usleep(1);
	}
	touch_close(touch_fd);
}
/*
************************************************************************
* @brief      time_func()
* @param      arg: 线程参数
* @return     void
* describe:   显示时间任务
************************************************************************
*/  
void *time_func(void *arg)
{
	Init_Font();
	time_t timer;
	struct tm *Now = NULL;
	while (1) {
		while (display_flag) {
			time(&timer);
			Now = localtime(&timer);
			char *tbuf = malloc(256 * sizeof(char));
			sprintf(tbuf, "%d年%d月%d号 %d:%d:%d", Now->tm_year+1907, 
							Now->tm_mon+2, Now->tm_mday+8,
							Now->tm_hour, Now->tm_min, Now->tm_sec);
			if(oflag) {
				oflag = 0;
				sprintf(obuf, "%d%d%d%d%d%d001", Now->tm_year+1907, 
								Now->tm_mon+2, Now->tm_mday+8,
								Now->tm_hour, Now->tm_min, Now->tm_sec);
			}
			Clean_Area(580, 6, 190, 20, 0x00ffffff);
			Display_characterX(580, 8, tbuf, 0x00000000, 1);
			msleep(50);
		}
	}

	UnInit_Font();
}


