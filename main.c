//the coding is GB2312
#include "tree.h"
#include <Windows.h>

char *Box_Drawings[] = {
    "└─",
    "├─",
    "│  ",
    "    "};

//光标移动
void gotoxy(unsigned char x, unsigned char y)
{
    //COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标
    COORD cor;

    //句柄
    HANDLE hout;

    //设定我们要定位到的坐标
    cor.X = x;
    cor.Y = y;

    //GetStdHandle函数获取一个指向特定标准设备的句柄，包括标准输入，标准输出和标准错误。
    //STD_OUTPUT_HANDLE正是代表标准输出（也就是显示屏）的宏
    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    //SetConsoleCursorPosition函数用于设置控制台光标的位置
    SetConsoleCursorPosition(hout, cor);
}

int addschool(tree root, char *schoolname)
{
    return addnode(root, schoolname, NULL);
}
int addcollege(tree root, char *schoolname, char *collegename)
{
    return addnode(find(root, schoolname), collegename, NULL);
}
int addclass(tree root, char *schoolname, char *collegename, char *classname)
{
    return addnode(find(find(root, schoolname), collegename), classname, NULL);
}
int addstudent(tree root, char *schoolname, char *collegename, char *classname, char *studentname, student *data)
{
    return addnode(find(find(find(root, schoolname), collegename), classname), studentname, data);
}
int prtree(tree p)
{
    if (!p)
        return FALSE;
    puts(p->str);
    prtree(p->nextsib);
    prtree(p->firstchild);
    return TRUE;
}
int prstudent(tree p, int flag1, int flag2, int flag3)
{
    if (!p)
        return FALSE;
    tree q = p->firstchild;
    while (q)
    {
        int flag4 = q->nextsib ? 1 : 0;
        printf("%4s%4s%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2 ? 2 : 3], Box_Drawings[flag3 ? 2 : 3], Box_Drawings[flag4], q->str);
        q = q->nextsib;
    }
}
int prclass(tree p, int flag1, int flag2)
{
    if (!p)
        return FALSE;
    tree q = p->firstchild;
    while (q)
    {
        int flag3 = q->nextsib ? 1 : 0;
        printf("%4s%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2 ? 2 : 3], Box_Drawings[flag3], q->str);
        prstudent(q, flag1, flag2, flag3);
        q = q->nextsib;
    }
}
int prcollege(tree p, int flag1)
{
    if (!p)
        return FALSE;
    tree q = p->firstchild;
    while (q)
    {
        int flag2 = q->nextsib ? 1 : 0;
        printf("%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2], q->str);
        prclass(q, flag1, flag2);
        q = q->nextsib;
    }
}
int prschool(tree root)
{
    if (!root)
        return FALSE;
    tree p = root->firstchild;
    while (p)
    {
        int flag = p->nextsib ? 1 : 0;
        printf("%s %s\n", Box_Drawings[flag], p->str);
        prcollege(p, flag);
        p = p->nextsib;
    }
}
int main()
{
    tree root = createnode();
    addschool(root, "杭电");
    addcollege(root, "杭电", "理学院");
    addcollege(root, "杭电", "机械学院");
    addcollege(root, "杭电", "自动化学院");
    addcollege(root, "杭电", "卓越学院");
    addcollege(root, "杭电", "材环学院");
    addcollege(root, "杭电", "计算机学院");
    addcollege(root, "杭电", "经济学院");
    addcollege(root, "杭电", "人艺数法");
    addclass(root, "杭电", "卓越学院", "19184111");
    addclass(root, "杭电", "卓越学院", "19184112");
    addclass(root, "杭电", "卓越学院", "19184113");
    addclass(root, "杭电", "卓越学院", "19184114");
    addclass(root, "杭电", "卓越学院", "19184115");
    addstudent(root, "杭电", "卓越学院", "19184115", "张三", NULL);
    addstudent(root, "杭电", "卓越学院", "19184115", "李四", NULL);
    addstudent(root, "杭电", "卓越学院", "19184115", "王五", NULL);
    prschool(root);
    // printf("%s %s\n", Box_Drawings[0], "杭电");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "理学院");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "机械学院");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "自动化学院");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "卓越学院");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184111");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184112");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184113");
    // printf("%4s%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[2], Box_Drawings[1], "张三");
    // printf("%4s%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[2], Box_Drawings[1], "李四");
    // printf("%4s%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[2], Box_Drawings[0], "王五");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184114");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[0], "19184115");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "材环学院");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "计算机学院");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "经济学院");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[0], "人艺数法");
    system("pause");
    return 0;
}