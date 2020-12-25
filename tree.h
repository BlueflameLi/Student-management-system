#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#define TRUE 1
#define FALSE 0
typedef struct node
{
    char *str;
    student *data;
    struct node *firstchild, *nextsib, *parents;
} node, *tree;

//创建节点
tree createnode();

//p添加一个儿子
int addnode(tree p, char *name, student *data);

//p的儿子里寻找name
tree find(tree p, char *name);
#endif