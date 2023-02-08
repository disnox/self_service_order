/*
************************************************************************
* file name: dir.c
* author: 苏尚宇
* date: Wed Dec 21 11:45:48 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "dir.h"

dir_t dir_bmp;

/*
*************************************************************************
* @brief 	  stat_dir()
* @param      name: 文件名
* @return     bool: 返回是否为目录的布尔值
* describe:   判断文件是否是一个目录
************************************************************************
*/
bool stat_dir(char *name)
{
	//获取文件属性,包括符号文件
	struct stat buf;
	lstat(name, &buf);
	
	//判断是否是一个目录
	if( !S_ISDIR(buf.st_mode) ) {
		printf("%s不是一个目录\n", name);
		return false;
	}
	return true;
}
/*
*************************************************************************
* @brief 	  file_type()
* @param      path: 指定目录
*			  xxx_type: 后缀名类型
*			  array: 用于存储符合条件的文件路径
* @return     void
* describe:   找出指定目录的指定后缀文件
************************************************************************
*/
void file_type(char *path, const char *xxx_type, char *array[])
{
	//打开目录,判断文件类型
	//1. 打开目录
	DIR *dp = opendir(path);
	if(dp == NULL) {
		perror("opendir() fail");
		return ;
	}
	
	//读取目录项
	struct dirent *ep = NULL;

	int i = 0;
	
	while(1) {
		array[i] = malloc(50 * sizeof(char));
		strcpy(array[i], path);
		//读取当前目录指针dp指向的目录项,读到的内容返回到ep
		//读成功后把目录指针dp偏移到下一个目录项
		ep = readdir(dp);
		if(ep == NULL && errno == 0) {	//读完所有目录项
			break;
		}
		if(ep == NULL) {	//出错
			perror("readdir() fail");
			return ;
		}
		
		// 忽略.和..
		if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0) {
			continue;
		}
			
		//忽略所有隐藏文件
		if(ep->d_name[0] == '.') {
			continue;
		}
						
		if( strstr(ep->d_name, xxx_type) ) {	//找到判断为真
			strcat(array[i], ep->d_name);
			printf("%s\n", array[i]);
			i++;
		}
	}
	//关闭目录
	closedir(dp);
}

/*
*************************************************************************
* @brief 	  file_bmp()
* @param      path: 指定目录
*			  xxx_type: 后缀名类型
*			  array: 用于存储符合条件的文件路径
* @return     void
* describe:   找出目录中的图片
************************************************************************
*/
int file_bmp(char *path, const char *xxx_type, char *array[])
{
	if( !stat_dir(path) ) {
		return 1;
	}
	file_type(path, xxx_type, array);

	return 0;
}
/*
*************************************************************************
* @brief 	  bmp_init()
* @param      void
* @return     void
* describe:   图片初始化
************************************************************************
*/
void bmp_init(void)
{
	dir_bmp.advbmp_name = malloc(50 * sizeof(char*));
	dir_bmp.bobmp_name = malloc(50 * sizeof(char*));
	dir_bmp.cha1bmp_name = malloc(50 * sizeof(char*));
	dir_bmp.cha2bmp_name = malloc(50 * sizeof(char*));
	dir_bmp.soupbmp_name = malloc(50 * sizeof(char*));
	dir_bmp.winebmp_name = malloc(50 * sizeof(char*));

	file_bmp(advbmp, bmp, dir_bmp.advbmp_name);
	file_bmp(bobmp, bmp, dir_bmp.bobmp_name);
	file_bmp(cha1bmp, bmp, dir_bmp.cha1bmp_name);
	file_bmp(cha2bmp, bmp, dir_bmp.cha2bmp_name);
	file_bmp(soupbmp, bmp, dir_bmp.soupbmp_name);
	file_bmp(winebmp, bmp, dir_bmp.winebmp_name);
}

