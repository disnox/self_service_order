/*
************************************************************************
* file name: display.h
* author: 苏尚宇
* date: Wed Dec 21 15:15:10 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _DISPLAY_H__
#define _DISPLAY_H__

#include "any_bmp.h"

// 最多显示
#define MAX_DISPLAY_ITEM 18

int oflag; 
extern char sbuf[10];

typedef enum {
    ADV_PAGE, 
    BO_PAGE,
    CHA1_PAGE,
    CHA2_PAGE,
    SOUP_PAGE,
    WINE_PAGE,
} page_t;

extern void display_nested_page(lcd_t *lcd, page_t page, int nested_page, int x, int y); 

extern void display_advbmp(lcd_t *lcd, char **array);
extern void display_home(lcd_t *lcd);
extern void display_order(lcd_t *lcd);
extern void display_choice(lcd_t *lcd);

extern void display_stock(lcd_t *lcd, page_t page, int id, int num, int bmp_id);

extern void display_cha1_stock(lcd_t *lcd, page_t page);
extern void display_cha2_stock(lcd_t *lcd, page_t page);
extern void display_soup_stock(lcd_t *lcd, page_t page);
extern void display_wine_stock(lcd_t *lcd, page_t page);

extern void display_down(lcd_t *lcd, page_t page);
extern void display_up(lcd_t *lcd, page_t page);

extern void display_less(lcd_t *lcd, page_t page);
extern void display_many(lcd_t *lcd, page_t page);

extern void display_menu_on_lcd(lcd_t *lcd);


#endif
