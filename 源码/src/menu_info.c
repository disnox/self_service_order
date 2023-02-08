/*
************************************************************************
* file name: food_info.c
* author: 苏尚宇
* date: Fri Dec 23 09:56:17 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "menu_info.h"
#include "font.h"
#include "control.h"

/*
************************************************************************
* @brief      init_menu_list()
* @param      void
* @return     void
* describe:   初始化菜单
************************************************************************
*/  
void init_menu_list(void)
{
	INIT_LIST_HEAD(&menu_list);
	load_menu_from_file("menu.txt");
	traverse_menu_list();
}

/*
************************************************************************
* @brief      add_menu_item()
* @param      id: 项目的唯一标识
*			  name: 项目名称
*			  price: 项目价格
*			  stock: 项目当前库存
* @return     void
* describe:   添加项目到菜单
************************************************************************
*/  
void add_menu_item(unsigned int id, char *name, unsigned int price, unsigned int stock)
{
	kernel_list_node *item = (kernel_list_node *)malloc(sizeof(kernel_list_node));

	item->menu_info.id = id;
	strcpy(item->menu_info.name, name);
	item->menu_info.price = price;
	item->menu_info.stock = stock;
	item->menu_info.sold = 0;

	list_add_tail(&(item->point_node), &menu_list);
}
/*
************************************************************************
* @brief      traverse_menu_list()
* @param      void
* @return     void
* describe:   遍历菜单项
************************************************************************
*/  
void traverse_menu_list(void)
{
	struct list_head *pos;
	kernel_list_node *item;

	list_for_each(pos, &menu_list)
	{
		item = list_entry(pos, kernel_list_node, point_node);
		printf("%u\t%s\t%u\t%u\t%d\n", item->menu_info.id, item->menu_info.name, item->menu_info.price, item->menu_info.stock, item->menu_info.sold);
	}
}
/*
************************************************************************
* @brief      load_menu_from_file()
* @param      filename: 文件名
* @return     void
* describe:   从文件中读取菜单并添加到链表中
************************************************************************
*/  
void load_menu_from_file(const char *filename)
{
	FILE *fp = fopen(filename, "r+");
	if (fp == NULL) {
		fprintf(stderr, "Error: Unable to open file %s\n", filename);
		return;
	}

	char name[30];
	unsigned int id, price, stock;
	while (fscanf(fp, "%u%s%u%u", &id, name, &price, &stock) == 4) {
		add_menu_item(id, name, price, stock);
	}

	fclose(fp);
}

/*
************************************************************************
* @brief      find_menu_item()
* @param      id: 菜单项编号
* @return     kernel_list_node: 菜单项的地址
* describe:   查找菜单项
************************************************************************
*/  
kernel_list_node *find_menu_item(unsigned int id)
{
	struct list_head *pos;
	kernel_list_node *item;

	list_for_each(pos, &menu_list)
	{
		item = list_entry(pos, kernel_list_node, point_node);
		if ( item->menu_info.id == id ) {
			// printf("%s\t%u\t%u\t%u\n", item->menu_info.name, item->menu_info.price, item->menu_info.stock, item->menu_info.sold);
			return item;
		}
	}

	return NULL;
}
/*
************************************************************************
* @brief      save_menu_to_file()
* @param      filename: 文件名
* @return     void
* describe:   将修改后的内容写入文件
************************************************************************
*/  
void save_menu_to_file(const char *filename)
{
	FILE *fp = fopen(filename, "w+");
	if (fp == NULL) {
		fprintf(stderr, "Error: Unable to open file %s\n", filename);
		return;
	}

	struct list_head *pos;
	kernel_list_node *item;

	list_for_each(pos, &menu_list)
	{
		item = list_entry(pos, kernel_list_node, point_node);
		fprintf(fp, "%u %s %u %u\n", item->menu_info.id, item->menu_info.name, item->menu_info.price, item->menu_info.stock);
	}

	fclose(fp);
}
/*
************************************************************************
* @brief      print_menu_with_sold()
* @param      void
* @return     void
* describe:   打印sold大于0的项目
************************************************************************
*/  
void print_menu_with_sold(void)
{
    struct list_head *pos;
    kernel_list_node *item;

    list_for_each(pos, &menu_list)
    {
        item = list_entry(pos, kernel_list_node, point_node);
        if (item->menu_info.sold > 0)
        {
            printf("%u\t%s\t%u\t%u\t%d\n", item->menu_info.id, item->menu_info.name, item->menu_info.price, item->menu_info.stock, item->menu_info.sold);
        }
    }
}
/*
************************************************************************
* @brief      sold_init()
* @param      void
* @return     void
* describe:   初始化sold为0
************************************************************************
*/  
void sold_init(void)
{
    struct list_head *pos;
    kernel_list_node *item;

    list_for_each(pos, &menu_list)
    {
        item = list_entry(pos, kernel_list_node, point_node);
        item->menu_info.sold = 0;
    }
}

