/*
************************************************************************
* file name: any_bmp.c
* author: 苏尚宇
* date: Wed Dec 21 11:41:11 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "any_bmp.h"
#include "main.h"

/*
************************************************************************
* @brief      lcd_init()
* @param      lcd: lcd显示图片相关参数结构体
* @return     成功和失败标志
* describe:   图片初始化
************************************************************************
*/  
int lcd_init(lcd_t *lcd)
{
	// 1. 打开液晶屏文件
	lcd->fd = open(LCD_DEV, O_RDWR);
	if (lcd->fd == -1) {
		return errno;
	}

	// 映射显存
	lcd->FB = mmap(NULL, LCD_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,lcd->fd,0);
	if (lcd->FB == MAP_FAILED) {
		return errno;
	}

	return 0;
}

/*
************************************************************************
* @brief      lcd_close()
* @param      lcd: lcd显示图片相关参数结构体
* @return     void
* describe:   资源释放
************************************************************************
*/  
void lcd_close(lcd_t *lcd)
{
	munmap(lcd->FB, LCD_SIZE);
	close(lcd->fd);
}

/*
************************************************************************
* @brief 	  display_stock()
* @param      lcd: lcd显示图片相关参数结构体
*			  bmpname: 图片路径字符串
*			  x: 图片x坐标 y: 图片y坐标
* @return     void
* describe:   显示任意图片到指定坐标
************************************************************************
*/   
void any_bmp(lcd_t *lcd, const char *bmpname, int x, int y)
{
	if (lcd == NULL || bmpname == NULL) {
		printf("参数无效\n");
		exit(0);
	}

	struct bmp_info bmp;

	// 打开图片
	bmp.fd = open(bmpname, O_RDONLY);
	if (bmp.fd == -1) {
		printf("%s ", bmpname);
		perror("open() fail");
		exit(0);
	}

	struct bitmap_header bh;
	read(bmp.fd, &bh, sizeof(struct bitmap_header));
	struct bitmap_info bi;
	read(bmp.fd, &bi, sizeof(struct bitmap_info));
	bmp.w = bi.width;
	bmp.h = bi.height;
	bmp.bpp = bi.bit_count;	 // 每个像素点多少位
	bmp.size = bh.size - 54; // 位图数据读出的大小，包括填充的0
	bmp.row_size = (bh.size - 54) / bmp.h;
	printf("x：%d,  y = %d\n", x, y);
	printf("像素宽：%d\n", bmp.w);
	printf("像素高：%d\n", bmp.h);
	printf("没个素位数：%d\n", bmp.bpp);
	printf("整个位图大小：%d\n", bmp.size);
	printf("位图一行大小：%d\n", bmp.row_size);

	// 判断起始位置和图片像素宽高是否越界
	if (bmp.w + x > 800 || bmp.h + y > 480) {
		printf("超出屏幕范围\n");
	}

	// 读一行，映射一行的数据
	char *bmp_row_buf = calloc(1, bmp.row_size);
	int *lcd_row_buf = calloc(bmp.w, sizeof(int));
	int i, j, k = 0;

	for (j = 0; j < bmp.h; j++) {
		read(bmp.fd, bmp_row_buf, bmp.row_size);
		for (i = 0; i < bmp.w; i++) {
			lcd_row_buf[i] = bmp_row_buf[k + 0] | bmp_row_buf[k + 1] << 8 | bmp_row_buf[k + 2] << 16;
			k += 3;
		}
		k = 0;

		memcpy(lcd->FB + (bmp.h - j - 1 + y) * 800 + x, lcd_row_buf, bmp.w * 4);
	}

	free(bmp_row_buf);
	free(lcd_row_buf);
	// 关闭BMP
	close(bmp.fd);
}


