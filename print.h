//the coding is UTF-8
#ifndef _PRINT_H_
#define _PRINT_H_

#include <Windows.h>
#include "tree.h"
#define MINLINE (lastline < 30 ? 30 : lastline)

//绘制树的字符
char *Box_Drawings[4];

//最后一行的坐标
int lastline;

//用户头
char *head;

//光标移动
void gotoxy(unsigned char x, unsigned char y);

//打印当前路径
int prfa(tree p);

//打印用户头
void prhead(tree p);

//打印界面
void printerface(tree p);

//递归打印目录树
int prtree2(tree p, int *flag, int depth);

//打印目录树
int prtree(tree root);

//清空右侧显示区
void cls();

#endif