#ifndef _ANY_BMP_H_
#define _ANY_BMP_H_

#define LCD_DEV		"/dev/fb0"
#define LCD_SIZE	800*480*4

// BMP文件头（14字节）
struct bitmap_header
{
    	short type;// 位图文件的类型，必须为BM(1-2字节）
    	int size;// 位图文件的大小，以字节为单位（3-6字节）
    	short reserved1;// 位图文件保留字，必须为0(7-8字节）
    	short reserved2;// 位图文件保留字，必须为0(9-10字节）
    	int offbits;// 位图数据的起始位置，以相对于位图（11-14字节）
                     // 文件头的偏移量表示，以字节为单位
}__attribute__((packed));

//位图信息头（40字节）
struct bitmap_info
{
	int size;// 本结构所占用字节数（15-18字节）	
	int width;// 位图的宽度，以像素为单位（19-22字节）
	int height;// 位图的高度，以像素为单位（23-26字节）
	short planes;// 目标设备的级别，必须为1(27-28字节）

	short bit_count;// 每个像素所需的位数，必须是1（双色），（29-30字节）
						// 4(16色），8(256色）或24（真彩色）之一
	int compression;// 位图压缩类型，必须是 0（不压缩），（31-34字节）
						// 1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
	int size_img;// 位图的大小，以字节为单位（35-38字节）
	int X_pel;// 位图水平分辨率，每米像素数（39-42字节）
	int Y_pel;// 位图垂直分辨率，每米像素数（43-46字节)
	int clrused;// 位图实际使用的颜色表中的颜色数（47-50字节）
	int clrImportant;// 位图显示过程中重要的颜色数（51-54字节）
}__attribute__((packed));

//显示图片所需的LCD的相关参数
typedef struct {
	int fd;
	int *FB;
}lcd_t;

struct bmp_info
{
	int fd;
	int w;
	int h;
	int bpp;	//每个像素的位数
	int row_size;
	int size;
};

extern int lcd_init(lcd_t *lcd);
extern void lcd_close(lcd_t *lcd);
extern void any_bmp(lcd_t *lcd, const char *bmpname, int x , int y);
extern void lcd_clear(lcd_t *lcd, int color);


#endif