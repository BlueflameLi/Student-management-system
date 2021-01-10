//the coding is GB2312

#include "print.h"

//绘制树的字符
char *Box_Drawings[4] = {
    "└─",
    "├─",
    "│  ",
    "   "};

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

//打印当前路径
int prfa(tree p)
{
    if (!p->parents)
        return FALSE;
    prfa(p->parents);
    strcat(head, "/");
    strcat(head, p->str);
}

//打印用户头
void prhead(tree p)
{

    if (p)
    {
        strcpy(head, "root@root : ～ ");
        prfa(p);
        strcat(head, " $ ");
    }
    gotoxy(0, MINLINE + 1);
    printf("%100s\n", " ");
    printf("%100s\n", " ");
    printf("%100s\n", " ");
    gotoxy(0, MINLINE + 1);
    printf("%s", head);
}

//打印界面
void printerface(tree p)
{
    gotoxy(0, 0);
    puts("*******************************************************************学生管理系统******************************************");
    for (int i = 1; i < MINLINE; i++)
    {
        gotoxy(35, i);
        putchar('*');
        gotoxy(120, i);
        putchar('*');
    }
    gotoxy(0, MINLINE);
    puts("*************************************************************************************************************************");
    gotoxy(125, 0);
    puts("help获取帮助");
    prhead(p);
}

//递归打印目录树
int prtree2(tree p, int *flag, int depth)
{
    if (!p)
        return FALSE;
    tree q = p->firstchild;
    while (q)
    {
        lastline++;
        flag[depth] = q->nextsib ? 1 : 0;
        putchar('*');
        for (int i = 0; i < depth; i++)
            printf("%s", Box_Drawings[flag[i] ? 2 : 3]);
        printf("%s %s\n", Box_Drawings[flag[depth]], q->str);
        prtree2(q, flag, depth + 1);
        q = q->nextsib;
    }
}

//打印目录树
int prtree(tree root)
{
    gotoxy(0, 1);
    for (int i = 1; i < MINLINE; i++)
        puts("*                                  ");
    gotoxy(0, 1);
    lastline = 1;
    int flag[5] = {0};
    prtree2(root, flag, 0);
    for (int i = lastline; i < MINLINE; i++)
        puts("*");
}

//清空右侧显示区
void cls()
{
    for (int i = 1; i < MINLINE; i++)
    {
        gotoxy(36, i);
        puts("                                                                                    ");
    }
    prhead(NULL);
}