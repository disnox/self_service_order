<h2 align="center">
🍽自助点餐系统
</h2><br>
<pre align="center">
 Build with 📷<a href="https://disnox.top">disnox</a> 
</pre>

<p align="center">
<br>
<a href="https://www.disnox.top/project">🖥 More Items</a>
<br>
<a href=" " rel="nofollow"><img src="https://img.shields.io/badge/-%F0%9F%92%BBLinux-blue"></a>
<a href=" " rel="nofollow"><img src="https://img.shields.io/badge/-%F0%9F%91%A8%E2%80%8D%F0%9F%92%BBC%2FC%2B%2B-blue"></a>
<a href=" " rel="nofollow"><img src="https://img.shields.io/badge/-%F0%9F%93%9Aproject-blue"></a>
</p>


## 1. 项目简介

本项目是一个基于 Linux 和 C语言 的自助点餐系统。该系统提供了一个友好的图形用户界面，顾客可以方便地查看餐厅的菜单并完成点餐操作。本系统的菜单信息和订单数据储存在文本文件中，通过控制台应用程序实现。此外，该系统还提供了一些常见的管理功能，例如添加或删除菜品，查询订单状态等。总的来说，本系统旨在提高餐厅的工作效率和提升顾客的用餐体验。

## 2. 软件环境

+ **GEC6818** 开发板
+ **Makefile** 工程管理

+ **VsCode** 代码编辑器
+ **Ubuntu22.04 Linux** 子系统
+ **MobaXterm_Personal_** SSH 软件

## 3. 项目实现

+ 本项目实现采用了Linux作为操作系统，以C语言为主要开发语言。
+ 用户界面采用C语言标准库函数实现，通过文件输入/输出（IO）实现键盘控制和屏幕输出。
+ 通过目录读取操作获取图片背景素材，通过函数调用以及枚举变量标志实现图形界面的调用。
+ 菜单信息和订单数据储存在文本文件中，使用 C语言 的文件读写函数实现数据的读写操作。
+ 为了捕获多种触摸事件，将其对应的坐标事件存入了一个文件中。通过读取文件并将读取到的数据保存在数组中，以索引数组的下标号判断点击事件是否发生。
+ 系统还利用了常见的数据结构：链表和数组，以实现对信息和数据的有效管理，从而提供一个高效且实用的自助点餐系统。

## 4. 程序设计流程

+ 广告界面--广告轮播--锁屏界面--选择界面--点菜选择--催促上菜
  + 点菜--特色菜--汤类--酒水
  + 催促--蜂鸣器
+ 订单页面--订单信息--订单号--价格--支付方式--返回点菜

## 5. 目录结构描述

```bash
.
├── Makefile				# Makefile工程配置文件
├── bin
│   └── main				# 可执行文件
├── doc						# 存放信息文件
│   ├── menu.txt			# 菜单文件
│   ├── menu.xlsx			# 菜单表格
│   ├── touch_range.txt		# 触摸事件文件
│   └── touch_range.xlsx	# 触摸事件表格
├── inc						# 存放.h文件
│   ├── any_bmp.h
│   ├── callback.h
│   ├── control.h
│   ├── dir.h
│   ├── display.h
│   ├── font.h
│   ├── kernel_list.h
│   ├── main.h
│   ├── menu_info.h
│   ├── thread.h
│   └── touch.h
├── lib						# 存放库文件
│   └── libfont.a
├── obj						# 存放.o文件
│   ├── any_bmp.o
│   ├── callback.o
│   ├── control.o
│   ├── dir.o
│   ├── display.o
│   ├── main.o
│   ├── menu_info.o
│   ├── thread.o
│   └── touch.o
└── src						# 存放.c文件
    ├── any_bmp.c			# 图片信息读取
    ├── callback.c			# 回调
    ├── control.c			# 系统逻辑控制
    ├── dir.c				# 读取目录
    ├── display.c			# 页面显示
    ├── main.c				# 主函数
    ├── menu_info.c			# 信息管理内核链表
    ├── thread.c			# 线程任务
    └── touch.c				# 触摸事件
```

## 6. 视频演示

<video id="video" controls="" preload="none">
    <source id="mp4" src="E:\Code\puresoft\self_order\录屏讲解\自助点餐系统演示视频.mp4" type="video/mp4">
</video>
