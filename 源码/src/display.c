/*
************************************************************************
* file name: display.c
* author: ������
* date: Wed Dec 21 15:15:01 CST 2022
* path: /mnt/e/Code/puresoft/����-��Ŀ����/Դ��
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "display.h"
#include "callback.h"
#include "control.h"
#include "menu_info.h"
#include "font.h"
#include "thread.h"
#include "dir.h"

char sbuf[10];

/*
************************************************************************
* @brief 	  display_nested_page()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
*			  nested_page: Ƕ��ҳ����
*			  x: ͼƬx���� y: ͼƬy����
* @return     void
* describe:   ����ҳ��������ʾ��Ӧ��Ƕ��ҳ��
************************************************************************
*/   
void display_nested_page(lcd_t *lcd, page_t page, int nested_page, int x, int y) 
{
	switch (page) {
		case ADV_PAGE:
			any_bmp(lcd, dir_bmp.advbmp_name[nested_page], x, y);
			break;
		case BO_PAGE:
			any_bmp(lcd, dir_bmp.bobmp_name[nested_page], x, y);
			break;
		case CHA1_PAGE:
			any_bmp(lcd, dir_bmp.cha1bmp_name[nested_page], x, y);
			break;
		case CHA2_PAGE:
			any_bmp(lcd, dir_bmp.cha2bmp_name[nested_page], x, y);
			break;
		case SOUP_PAGE:
			any_bmp(lcd, dir_bmp.soupbmp_name[nested_page], x, y);
			break;
		case WINE_PAGE:
			any_bmp(lcd, dir_bmp.winebmp_name[nested_page], x, y);
			break;
		default:
		// ��������ҳ������
		break;
	}
}

/*
************************************************************************
* @brief 	  display_advbmp()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  array: ���ͼƬ����
* @return     void
* describe:   ��ʾ���ҳ�棬������չʾ10�Ź��ͼƬ��ÿ1.5���л�һ��
************************************************************************
*/
void display_advbmp(lcd_t *lcd, char **array)
{
	int i;
	// 10�Ź��ͼƬ
	for (i=0; i<10; i++) {
		if (on_touch(controller[1].range)) {
			i = 0; x = 0; y = 0;
		}
		if (on_touch(controller[2].range)) {
			i = 1; x = 0; y = 0;
		}
		if (on_touch(controller[3].range)) {
			i = 2; x = 0; y = 0;
		}
		if (on_touch(controller[4].range)) {
			i = 3; x = 0; y = 0;
		}
		if (on_touch(controller[5].range)) {
			i = 4; x = 0; y = 0;
		}
		if (on_touch(controller[6].range)) {
			i = 5; x = 0; y = 0;
		}
		if (on_touch(controller[7].range)) {
			i = 6; x = 0; y = 0;
		}
		if (on_touch(controller[8].range)) {
			i = 7; x = 0; y = 0;
		}
		if (on_touch(controller[9].range)) {
			i = 8; x = 0; y = 0;
		}
		if (on_touch(controller[10].range)) {
			i = 9; x = 0; y = 0;
		}
		if (on_touch(controller[0].range)) {
			display_flag = lock_screen;
			display_nested_page(lcd, BO_PAGE, 0, 0, 0);
			display_nested_page(lcd, BO_PAGE, 1, 290, 441);
			break;
		}
		display_nested_page(lcd, ADV_PAGE, i, 0, 0);
		// 1.5���л�һ��
		msleep(1500);
	}
}

/*
************************************************************************
* @brief      display_home()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
* @return     void
* describe:   ��ʾ������������
************************************************************************
*/   
void display_home(lcd_t *lcd)
{
	if (on_touch(controller[11].range)) {
		int i = x;
		if (i > 470) {
			i = 470;
		}

		display_nested_page(lcd, BO_PAGE, 1, i, 441);
		if(x > 470) {
			x = 0; y = 0;
			display_flag = choice_screen;
			display_nested_page(lcd, BO_PAGE, 2, 0, 0);
		}
	}
}

/*
************************************************************************
* @brief      display_choice()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
* @return     void
* describe:   ѡ�����
************************************************************************
*/   
void display_choice(lcd_t *lcd)
{
	if (on_touch(controller[12].range)) {
		x = 0; y = 0;
		display_flag = order_screen;
		order_flag = package;
		display_nested_page(lcd, CHA1_PAGE, 0, 0, 0);
		display_nested_page(lcd, BO_PAGE, 9, 220, 180);
	}

	if (on_touch(controller[13].range)) {
		x = 0; y = 0;
		display_flag = lock_screen;
		beep();
	}
}

/*
************************************************************************
* @brief      display_order()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
* @return     void
* describe:   ��ʾ�˵����棬���ڴ������ĵ���¼�����ʱ�л�����Ӧ��Ƕ��ҳ��
************************************************************************
*/   
void display_order(lcd_t *lcd)
{
	if (on_touch(controller[14].range)) {
		x = 0; y = 0;
		order_flag = cha1_screen;
		display_nested_page(lcd, CHA1_PAGE, 0, 0, 0);
	}
	if (on_touch(controller[15].range)) {
		x = 0; y = 0;
		order_flag = soup_screen;
		display_nested_page(lcd, SOUP_PAGE, 0, 0, 0);
	}
	if (on_touch(controller[16].range)) {
		x = 0; y = 0;
		order_flag = wine_screen;
		display_nested_page(lcd, WINE_PAGE, 0, 0, 0);
	}
	if (on_touch(controller[19].range)) {
		x = 0; y = 0;
		oflag = 1;
		order_flag = pay_screen;
		display_nested_page(lcd, BO_PAGE, 5, 0, 0);
		Display_characterX(500, 355, obuf, 0x000000, 2);
	}
}

/*
************************************************************************
* @brief 	  display_stock()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
*			  id: �˵�����
*			  num: ���������
*			  bmp_id: λͼ���
* @return     void
* describe:   ����ҳ��������ʾ��Ӧ��Ƕ��ҳ��
************************************************************************
*/   
void display_stock(lcd_t *lcd, page_t page, int id, int num, int bmp_id)
{
	kernel_list_node *item = (kernel_list_node *)malloc(sizeof(kernel_list_node));

	item = find_menu_item(id);
	if (on_touch(controller[num].range)) {
		x = 0; y = 0;
		display_nested_page(lcd, page, bmp_id, 0, 0);
		sprintf(sbuf, "%d", item->menu_info.stock);	////��i��j��ʽ���浽����
		printf("%s\n", sbuf);
		Clean_Area(703, 333, 40, 25, 0x00ffffff);
	}
	Display_characterX(703, 333, sbuf, 0x00000000, 2);
}

/*
************************************************************************
* @brief 	  display_cha1_stock()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
* @return     void
* describe:   ��ʾCHA1����Ŀ����Ϣ
************************************************************************
*/   
void display_cha1_stock(lcd_t *lcd, page_t page)
{
	display_stock(lcd, page, 1, 20, 0);
	display_stock(lcd, page, 2, 23, 1);
	display_stock(lcd, page, 3, 26, 2);
	display_stock(lcd, page, 4, 29, 3);
	display_stock(lcd, page, 5, 32, 4);
	display_stock(lcd, page, 6, 35, 5);
	display_stock(lcd, page, 7, 38, 6);
	display_stock(lcd, page, 8, 41, 7);
	display_stock(lcd, page, 9, 44, 8);
	display_stock(lcd, page, 10, 47, 9);
	display_stock(lcd, page, 11, 50, 10);
	display_stock(lcd, page, 12, 53, 11);
	display_stock(lcd, page, 13, 56, 12);
	display_stock(lcd, page, 14, 59, 13);
}
/*
************************************************************************
* @brief 	  display_cha2_stock()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
* @return     void
* describe:   ��ʾCHA2����Ŀ����Ϣ
************************************************************************
*/   
void display_cha2_stock(lcd_t *lcd, page_t page)
{
	display_stock(lcd, page, 15, 20, 0);
	display_stock(lcd, page, 16, 23, 1);
	display_stock(lcd, page, 17, 26, 2);
	display_stock(lcd, page, 18, 29, 3);
	display_stock(lcd, page, 19, 32, 4);
	display_stock(lcd, page, 20, 35, 5);
	display_stock(lcd, page, 21, 38, 6);
	display_stock(lcd, page, 22, 41, 7);
	display_stock(lcd, page, 23, 44, 8);
	display_stock(lcd, page, 24, 47, 9);
	display_stock(lcd, page, 25, 50, 10);
	display_stock(lcd, page, 26, 53, 11);
	display_stock(lcd, page, 27, 56, 12);
	display_stock(lcd, page, 28, 59, 13);
}
/*
************************************************************************
* @brief 	  display_soup_stock()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
* @return     void
* describe:   ��ʾSOUP����Ŀ����Ϣ
************************************************************************
*/   
void display_soup_stock(lcd_t *lcd, page_t page)
{
	display_stock(lcd, page, 29, 20, 0);
	display_stock(lcd, page, 30, 23, 1);
	display_stock(lcd, page, 31, 26, 2);
	display_stock(lcd, page, 32, 29, 3);
	display_stock(lcd, page, 33, 32, 4);
	display_stock(lcd, page, 34, 35, 5);
	display_stock(lcd, page, 35, 38, 6);
	display_stock(lcd, page, 36, 41, 7);
	display_stock(lcd, page, 37, 44, 8);
	display_stock(lcd, page, 38, 47, 9);
	display_stock(lcd, page, 39, 50, 10);
	display_stock(lcd, page, 40, 53, 11);
	display_stock(lcd, page, 41, 56, 12);
	display_stock(lcd, page, 42, 59, 13);
}
/*
************************************************************************
* @brief 	  display_wine_stock()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
* @return     void
* describe:   ��ʾWINE����Ŀ����Ϣ
************************************************************************
*/   
void display_wine_stock(lcd_t *lcd, page_t page)
{
	display_stock(lcd, page, 43, 20, 0);
	display_stock(lcd, page, 44, 23, 1);
	display_stock(lcd, page, 45, 26, 2);
	display_stock(lcd, page, 46, 29, 3);
	display_stock(lcd, page, 47, 32, 4);
	display_stock(lcd, page, 48, 35, 5);
	display_stock(lcd, page, 49, 38, 6);
	display_stock(lcd, page, 50, 41, 7);
	display_stock(lcd, page, 51, 44, 8);
	display_stock(lcd, page, 52, 47, 9);
	display_stock(lcd, page, 53, 50, 10);
	display_stock(lcd, page, 54, 53, 11);
	display_stock(lcd, page, 55, 56, 12);
	display_stock(lcd, page, 56, 59, 13);
}

/*
************************************************************************
* @brief 	  display_down()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
* @return     void
* describe:   ���������17�Ĵ�����Χ���������ʾǶ��ҳ��3���ȴ�1���ӣ�Ȼ������ʾԭҳ��
************************************************************************
*/   
void display_down(lcd_t *lcd, page_t page)
{
	if (on_touch(controller[17].range)) {
		x = 0; y = 0;
		display_nested_page(lcd, BO_PAGE, 3, 220, 180);
		sleep(1);
		display_nested_page(lcd, page, 0, 0, 0);
	}
}
/*
************************************************************************
* @brief 	  display_up()
* @param      lcd: lcd��ʾͼƬ��ز����ṹ��
*			  page: ҳ������
* @return     void
* describe:   ���������18�Ĵ�����Χ���������ʾǶ��ҳ��4���ȴ�1���ӣ�Ȼ������ʾԭҳ��

*/   
void display_up(lcd_t *lcd, page_t page)
{
	if (on_touch(controller[18].range)) {
		x = 0; y = 0;
		display_nested_page(lcd, BO_PAGE, 4, 220, 180);
		sleep(1);
		display_nested_page(lcd, page, 0, 0, 0);
	}
}

/*
************************************************************************
* @brief 	  display_less()
* @param      lcd: ָ��LCD��ʾ��ز����ṹ���ָ��
*			  page: ҳ������
* @return     void
* describe:   ��ʾǶ��ҳ��7���ȴ�1���ӣ�Ȼ������ʾԭҳ��
************************************************************************
*/
void display_less(lcd_t *lcd, page_t page)
{
	display_nested_page(lcd, BO_PAGE, 7, 220, 180);
	sleep(1);
	display_nested_page(lcd, page, 0, 0, 0);
}
/*
************************************************************************
* @brief 	  display_many()
* @param      lcd: ָ��LCD��ʾ��ز����ṹ���ָ��
*			  page: ҳ������
* @return     void
* describe:   ��ʾǶ��ҳ��6���ȴ�1���ӣ�Ȼ������ʾԭҳ��
************************************************************************
*/
void display_many(lcd_t *lcd, page_t page)
{
	display_nested_page(lcd, BO_PAGE, 6, 220, 180);
	sleep(1);
	display_nested_page(lcd, page, 0, 0, 0);
}
/*
************************************************************************
* @brief 	  display_menu_on_lcd()
* @param      lcd: ָ��LCD��ʾ��ز����ṹ���ָ��
* @return     void
* describe:   ��ʾ����ҳ���������Ϣ
************************************************************************
*/
void display_menu_on_lcd(lcd_t *lcd)
{
    char buf[MAX_DISPLAY_ITEM][50] = {" "};
	char mbuf[10];
    int i = 0, j = 0, y1 = 70;
	int money = 0;
	static int flag = 0;
    struct list_head *pos;
    kernel_list_node *item;

    list_for_each(pos, &menu_list)
    {
        item = list_entry(pos, kernel_list_node, point_node);
        if (item->menu_info.sold > 0)
        {
			money = money + item->menu_info.price * item->menu_info.sold;
            sprintf(buf[i], "%s  %dԪ  %d��", item->menu_info.name, item->menu_info.price, item->menu_info.sold);
			i++;
        }
    }

	sprintf(mbuf, "%d", money);
	Display_characterX(490, 416, mbuf, 0x000000, 2);

	if(flag == 0) {
		for (j = 0; j < 9; j++)
		{
			Display_characterX(30, y1, buf[j], 0x000000, 2);
			y1 += 35;
		}
	}

	if (on_touch(controller[65].range)) {
		y1 = 70;
		flag = 1;
		x = 0; y = 0;
		display_nested_page(lcd, BO_PAGE, 5, 0, 0);
		for (j = 10; j < 18; j++)
		{
			Display_characterX(30, y1, buf[j], 0x000000, 2);
			y1 += 35;
		}
	}

	if (on_touch(controller[66].range)) {
		y1 = 70;
		flag = 0;
		x = 0; y = 0;
		display_nested_page(lcd, BO_PAGE, 5, 0, 0);
	}

	Display_characterX(500, 355, obuf, 0x000000, 2);
}

