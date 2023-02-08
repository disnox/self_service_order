/*
************************************************************************
* file name: callback.h
* author: 苏尚宇
* date: Fri Dec 23 15:01:51 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _CALLBACK_H__
#define _CALLBACK_H__

// 定义点击范围结构体
typedef struct {
    int x1;     // 坐标范围
    int x2;
    int y1;
    int y2;
    int num;
    char name[30];
}touch_range_t;

// 定义回调函数类型
typedef int (*touch_callback_t)(touch_range_t range, int x, int y);

// 触摸屏控制器结构体
typedef struct {
    touch_range_t range;
    touch_callback_t callback;
}touch_controller_t;

extern touch_controller_t controller[100];

extern int on_touch(touch_range_t range);


#endif
