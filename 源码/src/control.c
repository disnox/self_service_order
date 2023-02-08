/*
************************************************************************
* file name: src/control.c
* author: 苏尚宇
* date: Tue Dec 20 14:33:39 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "callback.h"
#include "control.h"
#include "any_bmp.h"
#include "menu_info.h"
#include "thread.h"
#include "font.h"

/*
************************************************************************
* @brief      click_init()
* @param      void
* @return     void
* describe:   触摸控制器坐标初始化
************************************************************************
*/  
void click_init(void)
{
	// 从文件中读取触摸屏控制器数组
    FILE *fp = fopen("touch_range.txt", "r");
    for (int i = 0; i < 68; i++) {
        fscanf(fp, "%d %s %d %d %d %d", &controller[i].range.num, controller[i].range.name, &controller[i].range.x1, &controller[i].range.x2, &controller[i].range.y1, &controller[i].range.y2);
    }
    fclose(fp);

    // 输出触摸屏控制器数组
    for (int i = 0; i < 68; i++) {
        printf("Controller[%d]: (%d, %d, %d, %d) - %s\n", controller[i].range.num, controller[i].range.x1, controller[i].range.x2, controller[i].range.y1, controller[i].range.y2, controller[i].range.name);
    }
}
/*
************************************************************************
* @brief      display_control()
* @param      lcd: lcd显示图片相关参数结构体
*			  array: 广告图片的路径数组
* @return     void
* describe:   根据display_flag的值决定显示哪种界面
************************************************************************
*/  
void display_control(lcd_t *lcd, char **array)
{
	switch (display_flag) {
		case poster_screen:
			display_advbmp(lcd, array);
			break;
		case lock_screen:
			display_home(lcd);
			break;
		case choice_screen:
			display_choice(lcd);
			break;
		case order_screen:
			display_order(lcd);
			break;
		default:
			break;
	}
}

/*
************************************************************************
* @brief      order_control()
* @param      lcd: lcd显示图片相关参数结构体
*			  array: 菜单图片数组
* @return     void
* describe:   根据订单状态显示相应的菜单页面，并实现页面间的切换
************************************************************************
*/  
void order_control(lcd_t *lcd, char **array)
{
    switch (order_flag) {
		case package:
			package_control(lcd);
			break;
		case cha1_screen:
			display_cha1_stock(lcd, CHA1_PAGE);
			cha1_screen_dishes(lcd, CHA1_PAGE);
			display_up(lcd, CHA1_PAGE);
			if (on_touch(controller[17].range)) {
				x = 0; y = 0;
				order_flag = cha2_screen;
				display_nested_page(lcd, CHA2_PAGE, 0, 0, 0);
			}
			break;
		case cha2_screen:
			display_cha2_stock(lcd, CHA2_PAGE);
			display_down(lcd, CHA2_PAGE);
			cha2_screen_dishes(lcd, CHA2_PAGE);
			if (on_touch(controller[18].range)) {
				x = 0; y = 0;
				order_flag = cha1_screen;
				display_nested_page(lcd, CHA1_PAGE, 0, 0, 0);
			}
			break;	
		case soup_screen:
			display_soup_stock(lcd, SOUP_PAGE);
			display_up(lcd, SOUP_PAGE);
			display_down(lcd, SOUP_PAGE);
			soup_screen_dishes(lcd, SOUP_PAGE);
			break;
		case wine_screen:
			display_wine_stock(lcd, WINE_PAGE);
			display_up(lcd, WINE_PAGE);
			display_down(lcd, WINE_PAGE);
			wine_screen_dishes(lcd, WINE_PAGE);
			break;
		case pay_screen:
			display_menu_on_lcd(lcd);
			ret_pay_order_screen(lcd);
			break;
		default:
			break;
	}

}
/*
************************************************************************
* @brief      package_control()
* @param      lcd: lcd显示图片相关参数结构体
* @return     void
* describe:   根据订单状态显示相应的菜单页面，并实现页面间的切换
************************************************************************
*/  
void package_control(lcd_t *lcd)
{
	int flag = 0;
    kernel_list_node *item;

	if (on_touch(controller[67].range)) {
		flag = 1;
		oflag = 1;
		x = 0; y = 0;
		order_flag = pay_screen;
		display_nested_page(lcd, BO_PAGE, 5, 0, 0);
	} 
	if(flag) {
		item = find_menu_item(1);
		item->menu_info.sold = 1;
		item = find_menu_item(3);
		item->menu_info.sold = 1;
		item = find_menu_item(25);
		item->menu_info.sold = 1;
		item = find_menu_item(27);
		item->menu_info.sold = 1;
		item = find_menu_item(34);
		item->menu_info.sold = 1;
		item = find_menu_item(43);
		item->menu_info.sold = 1;
	}
}
/*
************************************************************************
* @brief 	  display_stock()
* @param      lcd: lcd显示图片相关参数结构体
*			  page: 页面类型
*			  id: 菜单项编号
*			  x1: 图片x坐标 y1: 图片y坐标
*			  num1: 控制器编号1
*			  num2: 控制器编号2
* @return     void
* describe:   根据页面类型显示相应的嵌套页面
************************************************************************
*/   
void order_dishes(lcd_t *lcd, page_t page, unsigned int id, int x1, int y1, int num1, int num2)
{
	kernel_list_node *item = (kernel_list_node *)malloc(sizeof(kernel_list_node));
	char buf[10];

	item = find_menu_item(id);
	
	sprintf(buf, "%d", item->menu_info.sold);	////把i和j格式化存到数组
	Display_characterX(x1, y1, buf, 0x00000000, 2);

	if (on_touch(controller[num1].range)) {
		x = 0; y = 0;
		item->menu_info.sold++;
		if(item->menu_info.sold < 9)
			item->menu_info.stock--;
		if(item->menu_info.sold > 9) {
			item->menu_info.sold = 9;
			display_many(lcd, page);
		}
		Clean_Area(x1, y1, 25, 25, 0x00ffffff);
		Clean_Area(703, 333, 40, 25, 0x00ffffff);
		printf("%u\n", item->menu_info.sold);
	}

	if (on_touch(controller[num2].range)) {
		x = 0; y = 0;
		item->menu_info.sold--;
		if(item->menu_info.sold > 0)
			item->menu_info.stock++;
		if(item->menu_info.sold < 0) {
printf("----------------------------------------------------\n");
			item->menu_info.sold = 0;
			display_less(lcd, page);
		}
		Clean_Area(x1, y1, 25, 25, 0x00ffffff);
		Clean_Area(703, 333, 40, 25, 0x00ffffff);
		printf("%u\n", item->menu_info.sold);
	}
}
/*
************************************************************************
* @brief      cha1_screen_dishes()
* @param      lcd: lcd显示图片相关参数结构体
*			  page: 页面类型
* @return     void
* describe:   在CHA1上根据页面类型订购菜品
************************************************************************
*/  
void cha1_screen_dishes(lcd_t *lcd, page_t page)
{
	order_dishes(lcd, page, 1, 131, 95, 21, 22);
	order_dishes(lcd, page, 2, 131, 132, 24, 25);
	order_dishes(lcd, page, 3, 131, 169, 27, 28);
	order_dishes(lcd, page, 4, 131, 206, 30, 31);
	order_dishes(lcd, page, 5, 131, 243, 33, 34);
	order_dishes(lcd, page, 6, 131, 280, 36, 37);
	order_dishes(lcd, page, 7, 131, 317, 39, 40);
	order_dishes(lcd, page, 8, 315, 95, 42, 43);
	order_dishes(lcd, page, 9, 315, 132, 45, 46);
	order_dishes(lcd, page, 10, 315, 169, 48, 49);
	order_dishes(lcd, page, 11, 315, 206, 51, 52);
	order_dishes(lcd, page, 12, 315, 243,54, 55);
	order_dishes(lcd, page, 13, 315, 280, 57, 58);
	order_dishes(lcd, page, 14, 315, 317, 60, 61);
}
/*
************************************************************************
* @brief      cha2_screen_dishes()
* @param      lcd: lcd显示图片相关参数结构体
*			  page: 页面类型
* @return     void
* describe:   在CHA2上根据页面类型订购菜品
************************************************************************
*/  
void cha2_screen_dishes(lcd_t *lcd, page_t page)
{
	order_dishes(lcd, page, 15, 131, 95, 21, 22);
	order_dishes(lcd, page, 16, 131, 132, 24, 25);
	order_dishes(lcd, page, 17, 131, 169, 27, 28);
	order_dishes(lcd, page, 18, 131, 206, 30, 31);
	order_dishes(lcd, page, 19, 131, 243, 33, 34);
	order_dishes(lcd, page, 20, 131, 280, 36, 37);
	order_dishes(lcd, page, 21, 131, 317, 39, 40);
	order_dishes(lcd, page, 22, 315, 95, 42, 43);
	order_dishes(lcd, page, 23, 315, 132, 45, 46);
	order_dishes(lcd, page, 24, 315, 169, 48, 49);
	order_dishes(lcd, page, 25, 315, 206, 51, 52);
	order_dishes(lcd, page, 26, 315, 243,54, 55);
	order_dishes(lcd, page, 27, 315, 280, 57, 58);
	order_dishes(lcd, page, 28, 315, 317, 60, 61);
}
/*
************************************************************************
* @brief      soup_screen_dishes()
* @param      lcd: lcd显示图片相关参数结构体
*			  page: 页面类型
* @return     void
* describe:   在SOUP上根据页面类型订购菜品
************************************************************************
*/  
void soup_screen_dishes(lcd_t *lcd, page_t page)
{
	order_dishes(lcd, page, 29, 131, 95, 21, 22);
	order_dishes(lcd, page, 30, 131, 132, 24, 25);
	order_dishes(lcd, page, 31, 131, 169, 27, 28);
	order_dishes(lcd, page, 32, 131, 206, 30, 31);
	order_dishes(lcd, page, 33, 131, 243, 33, 34);
	order_dishes(lcd, page, 34, 131, 280, 36, 37);
	order_dishes(lcd, page, 35, 131, 317, 39, 40);
	order_dishes(lcd, page, 36, 315, 95, 42, 43);
	order_dishes(lcd, page, 37, 315, 132, 45, 46);
	order_dishes(lcd, page, 38, 315, 169, 48, 49);
	order_dishes(lcd, page, 39, 315, 206, 51, 52);
	order_dishes(lcd, page, 40, 315, 243,54, 55);
	order_dishes(lcd, page, 41, 315, 280, 57, 58);
	order_dishes(lcd, page, 42, 315, 317, 60, 61);
}
/*
************************************************************************
* @brief      wine_screen_dishes()
* @param      lcd: lcd显示图片相关参数结构体
*			  page: 页面类型
* @return     void
* describe:   在WINE上根据页面类型订购菜品
************************************************************************
*/  
void wine_screen_dishes(lcd_t *lcd, page_t page)
{
	order_dishes(lcd, page, 43, 131, 95, 21, 22);
	order_dishes(lcd, page, 44, 131, 132, 24, 25);
	order_dishes(lcd, page, 45, 131, 169, 27, 28);
	order_dishes(lcd, page, 46, 131, 206, 30, 31);
	order_dishes(lcd, page, 47, 131, 243, 33, 34);
	order_dishes(lcd, page, 48, 131, 280, 36, 37);
	order_dishes(lcd, page, 49, 131, 317, 39, 40);
	order_dishes(lcd, page, 50, 315, 95, 42, 43);
	order_dishes(lcd, page, 51, 315, 132, 45, 46);
	order_dishes(lcd, page, 52, 315, 169, 48, 49);
	order_dishes(lcd, page, 53, 315, 206, 51, 52);
	order_dishes(lcd, page, 54, 315, 243,54, 55);
	order_dishes(lcd, page, 55, 315, 280, 57, 58);
	order_dishes(lcd, page, 56, 315, 317, 60, 61);
}

/*
************************************************************************
* @brief      ret_pay_order_screen()
* @param      lcd: lcd显示图片相关参数结构体
* @return     void
* describe:   当用户选择支付时进行相应操作，如保存菜单、预定订单、显示相应的界面等
************************************************************************
*/  
void ret_pay_order_screen(lcd_t *lcd)
{
	if (on_touch(controller[62].range)||on_touch(controller[63].range)) {
		x = 0; y = 0;
		display_flag = choice_screen;
		order_flag = screen;
		save_menu_to_file("menu.txt");
		display_nested_page(lcd, BO_PAGE, 8, 220, 180);
		sleep(1);
		reserve_order("order.txt");
		display_nested_page(lcd, BO_PAGE, 2, 0, 0);
		save_menu_to_file("menu.txt");
		traverse_menu_list();
		sold_init();
	}

	if (on_touch(controller[64].range)) {
		x = 0; y = 0;
		order_flag = cha1_screen;
		display_nested_page(lcd, CHA1_PAGE, 0, 0, 0);
	}
}
/*
************************************************************************
* @brief      reserve_order()
* @param      filename: 文件名称
* @return     void
* describe:   保存用户订单文件
************************************************************************
*/  
void reserve_order(const char *filename)
{
	struct list_head *pos;
    kernel_list_node *item;
	int i = 0;

	FILE *fp = fopen(filename, "w+");
	if (fp == NULL) {
		fprintf(stderr, "Error: Unable to open file %s\n", filename);
		return;
	}

    list_for_each(pos, &menu_list)
    {
        item = list_entry(pos, kernel_list_node, point_node);
        if (item->menu_info.sold > 0)
        {
			i++;
			fprintf(fp, "%u %s %u %u\n", i, item->menu_info.name, item->menu_info.price, item->menu_info.sold);
        }
    }

	fclose(fp);
}
/*
************************************************************************
* @brief      beep()
* @param      void
* @return     int
* describe:   蜂鸣器
************************************************************************
*/  
int beep(void)
{
	int fd;
	int ret;
	fd = open("/dev/beep", O_RDWR);            //打开设备，成功返回0
	printf("**********************buzzer On*************************\n");
	ret = ioctl(fd, 0, 1);                 //BUZZER on
	msleep(500);
	printf("**********************buzzer Off************************\n");
	ret = ioctl(fd, 1, 1);                //BUZZER off	
	sleep(500);		
	close(fd);
}
