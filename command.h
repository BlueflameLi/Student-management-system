#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "print.h"
//命令帮助
char *cmdhelp[20];

//modify帮助
char *modifyhelp[10];

//find帮助
char *findhelp[15];

//lr显示的文字
char *lrstr[5];

//目前已去除相关命令，仅用于测试
int addschool(tree root, char *schoolname);
int addcollege(tree root, char *schoolname, char *collegename);
int addmajor(tree root, char *schoolname, char *collegename, char *majorname);
int addclass(tree root, char *schoolname, char *collegename, char *majorname, char *classname);
int addstudent(tree root, char *schoolname, char *collegename, char *majorname, char *classname, char *studentname, student *data);

//显示学生信息
int cat(tree p);

//显示子目录
int ls(tree p);

//更新界面
void update(tree root, tree p);

//查看帮助
void help();

//字符串分割
int strcut(char *str, char *token[], char *delim);

//查找路径
tree finddir(tree p, tree root, char *str);

//切换目录
int cd(tree *p, char *str, tree root);

//创建新目录
int create(tree *p, char *str, tree root);

//递归统计
int lr2(tree p, int *cnt);

//统计
int lr(tree p);

//删除目录
int rm(tree *p, char *str, tree root);

//重命名
int renme(tree p, char *newname);

//修改学生信息
int modify(tree p, char *str);

//移动学生
int mv(tree p, tree root, char *str);

//递归搜索
int search2(tree p, char *str[], int id, int sex, int age, tree *list, int *k);

//搜索
int search(tree p, tree root, char *str);

#endif