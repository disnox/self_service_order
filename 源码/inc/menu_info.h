/*
************************************************************************
* file name: food_info.h
* author: 苏尚宇
* date: Fri Dec 23 09:56:27 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _MENU_INFO_H__
#define _MENU_INFO_H__

#include "kernel_list.h"

struct list_head menu_list;

typedef struct {
    unsigned int id;       // 菜编号
    char name[30];          // 菜名
    unsigned int price;     // 价格
    unsigned int stock;     // 库存
    unsigned int sold;      // 购买数
}menu_item_t;

typedef struct {
    menu_item_t menu_info;          // 菜单结构体
    struct list_head point_node;    // 内核链表
}kernel_list_node;

extern void init_menu_list(void);
extern void add_menu_item(unsigned int id, char *name, unsigned int price, unsigned int stock);
extern void traverse_menu_list(void);
extern void load_menu_from_file(const char *filename);
extern kernel_list_node *find_menu_item(unsigned int id);
extern void save_menu_to_file(const char *filename);
extern void print_menu_with_sold(void);
extern void sold_init(void);

#endif
