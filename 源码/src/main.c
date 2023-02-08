/*
************************************************************************
* file name: main.c
* author: 苏尚宇
* date: Wed Dec 21 11:41:11 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "font.h"
#include "touch.h"
#include "any_bmp.h"
#include "thread.h"
#include "dir.h"
#include "display.h"
#include "menu_info.h"
#include "callback.h"
#include "control.h"
 
int main(int argc, char *argv[])
{
	lcd_t lcd;
	lcd_init(&lcd);

	Init_Font();		// 字库初始化
	bmp_init();			// 图片初始化
	init_menu_list();	// 菜单信息初始化
	click_init();		// 触摸初始化

	thread_init(touch_func, NULL);	// 触摸任务
	thread_init(time_func, NULL);	// 时间任务

	display_flag = poster_screen;	// 标志位初始化
	order_flag = screen;			// 标志位初始化
	
	sleep(1);
	// display_nested_page(&lcd, BO_PAGE, 5, 0, 0);
	// display_nested_page(&lcd, BO_PAGE, 3, atoi(argv[1]), atoi(argv[2]));
	// display_nested_page(&lcd, BO_PAGE, 9, 220, 180);
	// Clean_Area(atoi(argv[1]), atoi(argv[2]), 200, 90, BLACK);
	while(1) {
		display_control(&lcd, dir_bmp.advbmp_name);
		order_control(&lcd, dir_bmp.advbmp_name);
	}
	
	lcd_close(&lcd);
	UnInit_Font();

	return 0;
}
