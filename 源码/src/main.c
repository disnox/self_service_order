/*
************************************************************************
* file name: main.c
* author: ������
* date: Wed Dec 21 11:41:11 CST 2022
* path: /mnt/e/Code/puresoft/����-��Ŀ����/Դ��
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

	Init_Font();		// �ֿ��ʼ��
	bmp_init();			// ͼƬ��ʼ��
	init_menu_list();	// �˵���Ϣ��ʼ��
	click_init();		// ������ʼ��

	thread_init(touch_func, NULL);	// ��������
	thread_init(time_func, NULL);	// ʱ������

	display_flag = poster_screen;	// ��־λ��ʼ��
	order_flag = screen;			// ��־λ��ʼ��
	
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
