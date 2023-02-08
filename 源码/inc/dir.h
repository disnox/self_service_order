/*
************************************************************************
* file name: dir.h
* author: 苏尚宇
* date: Wed Dec 21 11:45:57 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _DIR_H__
#define _DIR_H__

#include <stdbool.h>

#define advbmp "bmp/advbmp/"
#define bobmp "bmp/bobmp/"
#define cha1bmp "bmp/fobmp/cha1/"
#define cha2bmp "bmp/fobmp/cha2/"
#define soupbmp "bmp/fobmp/soup/"
#define winebmp "bmp/fobmp/wine/"
#define bmp ".bmp"

typedef struct {
    char **advbmp_name;
    char **bobmp_name;
    char **cha1bmp_name;
    char **cha2bmp_name;
    char **soupbmp_name;
    char **winebmp_name;
}dir_t;

extern dir_t dir_bmp;

extern void bmp_init(void);
extern bool stat_dir(char *name);
extern void file_type(char *path, const char *xxx_type, char *array[]);
extern int file_bmp(char *path, const char *xxx_type, char *array[]);

#endif
