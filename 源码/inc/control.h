/*
************************************************************************
* file name: control.h
* author: 苏尚宇
* date: Fri Dec 23 15:44:26 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _CONTROL_H__
#define _CONTROL_H__

#include "display.h"



extern void click_init(void);
extern void display_control(lcd_t *lcd, char **array);
extern void order_control(lcd_t *lcd, char **array);
extern void order_dishes(lcd_t *lcd, page_t page, unsigned int id, int x, int y, int num1, int num2);
extern void package_control(lcd_t *lcd);
extern void cha1_screen_dishes(lcd_t *lcd, page_t page);
extern void cha2_screen_dishes(lcd_t *lcd, page_t page);
extern void soup_screen_dishes(lcd_t *lcd, page_t page);
extern void wine_screen_dishes(lcd_t *lcd, page_t page);
extern void ret_pay_order_screen(lcd_t *lcd);
extern void reserve_order(const char *filename);
extern int beep(void);

#endif
