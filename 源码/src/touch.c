
#include "main.h"
#include "touch.h"
#include "font.h"

/*
************************************************************************
* @brief      touch_init()
* @param      void
* @return     void
* describe:   触摸屏初始化
************************************************************************
*/  
int touch_init(void)
{
	// 1. 打开触摸屏设备文件
	// 以什么权限打开合适？ 只读
	int touch_fd = open(TOUCH_DEV, O_RDONLY);
	if(touch_fd == -1) {
		perror("open() TOUCH fail");
		exit(0);
	}
	return touch_fd;
}


/*
************************************************************************
* @brief      touch_close()
* @param      void
* @return     void
* describe:   关闭触摸屏文件
************************************************************************
*/  
void touch_close(int fd)
{
	close(fd);
}


/*
************************************************************************
* @brief      get_touch()
* @param      touch_fd: 文件标识
*			  x: x坐标 y: y坐标
* @return     void
* describe:   获取坐标
************************************************************************
*/  
void get_touch(int touch_fd, int *x, int *y)
{
	struct input_event buf;
	read(touch_fd, &buf, sizeof(buf));
	
	if(buf.type == EV_ABS)	{	//等于就是绝对事件
		if(buf.code == ABS_X)	//读到X轴
			*x = buf.value;
		else if(buf.code == ABS_Y)	//读到X轴
			*y = buf.value;
	}
	printf("(%d,%d)\n", *x, *y);
	
	if(*x > 400 && *x < 800)
		printf("屏幕右边\n");
	if(*x > 0 && *x < 400)
		printf("屏幕左边\n");
}
/*
************************************************************************
* @brief      get_xy()
* @param      touch_fd: 文件标识
*			  x: x坐标 y: y坐标
* @return     void
* describe:   获取坐标
************************************************************************
*/  
void get_xy(int touch_fd, int *x, int *y)
{
	struct input_event buf;
	while(1) {
		// 2.1 读到哪里？读到 struct input_event 结构体类型的变量中
		read(touch_fd, &buf, sizeof(struct input_event));
		
		// 2.2 判断事件的类型
		if(buf.type == EV_ABS) { //绝对位移事件
			// 判断事件的动作
			if(buf.code == ABS_X) {	//X轴事件
				*x = buf.value;	//蓝色边框
			}			//判断事件的状态(值)
			if(buf.code == ABS_Y) {	//Y轴事件
				*y = buf.value;	//蓝色边框
			}
		}
		if(buf.type == EV_KEY) {		//键盘事件，按压事件
			if(buf.code == BTN_TOUCH) {
				if(buf.value == 0) {	//默认值0，没有按下
					printf("松开\n");
					break;
				}
				else					//非0，事件发生，按下
					printf("按下\n");
			}
		}
	}
}



