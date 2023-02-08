/*
************************************************************************
* file name: callback.c
* author: 苏尚宇
* date: Fri Dec 23 15:01:44 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "callback.h"
#include "main.h"

touch_controller_t controller[100];
/*
************************************************************************
* @brief      on_touch()
* @param      range: 点击范围信息
* @return     0: 没有点击 1: 点击成功
* describe:   点击回调函数
************************************************************************
*/  
int on_touch(touch_range_t range) 
{
    if (range.x1 <= x && x <= range.x2 && range.y1 <= y && y <= range.y2) {
        printf("Touch 1: x=%d, y=%d\n", x, y);
        return 1;
    }
    return 0;
} 

