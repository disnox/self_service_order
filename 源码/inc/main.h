/*
************************************************************************
* file name: main.h
* author: 苏尚宇
* date: Wed Dec 21 11:34:57 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _MAIN_H__
#define _MAIN_H__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "kernel_list.h"

int x, y;

// 定义显示界面的枚举变量
typedef enum {
    poster_screen,  // 广告界面标志
    lock_screen,    // 锁屏界面标志
    choice_screen,  // 选择界面标志
    urge,           // 催促界面标志
    order_screen,   // 点菜界面标志
    payment_screen  // 支付界面标志
}flag1; 

// 定义显示界面的枚举变量
typedef enum {
    screen,         // 默认
    package,        // 套餐标志
    cha1_screen,    // 特色菜界面1标志
    cha2_screen,    // 特色菜界面2标志
    soup_screen,    // 汤菜界面标志
    wine_screen,    // 酒水界面标志
    pay_screen,     // 付款界面标志
}flag2; 

flag1 display_flag;
flag2 order_flag;

/* 生成毫秒级延时 */
static void msleep(unsigned msec)
{
    usleep(msec*1000);
}



#endif
