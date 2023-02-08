/*
************************************************************************
* file name: food_info.c
* author: ������
* date: Fri Dec 23 09:56:17 CST 2022
* path: /mnt/e/Code/puresoft/����-��Ŀ����/Դ��
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
* describe:   ��ʼ���˵�
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
* @param      id: ��Ŀ��Ψһ��ʶ
*			  name: ��Ŀ����
*			  price: ��Ŀ�۸�
*			  stock: ��Ŀ��ǰ���
* @return     void
* describe:   �����Ŀ���˵�
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
* describe:   �����˵���
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
* @param      filename: �ļ���
* @return     void
* describe:   ���ļ��ж�ȡ�˵�����ӵ�������
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
* @param      id: �˵�����
* @return     kernel_list_node: �˵���ĵ�ַ
* describe:   ���Ҳ˵���
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
* @param      filename: �ļ���
* @return     void
* describe:   ���޸ĺ������д���ļ�
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
* describe:   ��ӡsold����0����Ŀ
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
* describe:   ��ʼ��soldΪ0
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

