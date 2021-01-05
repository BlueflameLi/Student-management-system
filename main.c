//the coding is GB2312
#include "tree.h"
#include <Windows.h>
#define MINLINE (lastline < 30 ? 30 : lastline)
char *Box_Drawings[] = {
    "└─",
    "├─",
    "│  ",
    "   "};
char *cmdhelp[20] = {"命令              功能              示例",
                     "help             查看帮助           help",
                     "exit             退出程序           exit",
                     "ls               列出子目录         ls",
                     "cd               切换目录           cd 杭电、cd ..",
                     "create           新建目录           create 计算机学院",
                     "addschool        创建学校           addschool 杭电",
                     "addcollege       创建学院           addcollege 杭电 卓越学院",
                     "addmajor         创建专业           addmajor 杭电 卓越学院 计科",
                     "addclass         创建班级           addclass 杭电 卓越学院 计科 19184115",
                     "addstudent       创建学生           addstudent 杭电 卓越学院 计科 19184115 张三",
                     "lr               统计               lr 卓越学院、lr all"};
int lastline;
char *head;
char *lrstr[5] = {
    "共计%d个学校",
    "共计%d个学院",
    "共计%d个专业",
    "共计%d个班级",
    "共计%d个学生"};
char *catstr[10] = {"姓名：%s", "性别：%s", "年龄：%s", "学校：%s", "学院：%s", "专业：%s", "班级：%s", "学号：%s"};
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
int prfa(tree p)
{
    if (!p->parents)
        return FALSE;
    prfa(p->parents);
    strcat(head, "/");
    strcat(head, p->str);
}
void prhead(tree p)
{

    if (p)
    {
        strcpy(head, "root@root : ～ ");
        prfa(p);
        strcat(head, " $ ");
    }
    gotoxy(0, MINLINE + 1);
    printf("%80s\n", " ");
    printf("%80s\n", " ");
    printf("%80s\n", " ");
    gotoxy(0, MINLINE + 1);
    printf("%s", head);
}
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

int addschool(tree root, char *schoolname)
{
    return addnode(root, schoolname, NULL);
}
int addcollege(tree root, char *schoolname, char *collegename)
{
    return addnode(find(root, schoolname), collegename, NULL);
}
int addmajor(tree root, char *schoolname, char *collegename, char *majorname)
{
    return addnode(find(find(root, schoolname), collegename), majorname, NULL);
}
int addclass(tree root, char *schoolname, char *collegename, char *majorname, char *classname)
{
    return addnode(find(find(find(root, schoolname), collegename), majorname), classname, NULL);
}
int addstudent(tree root, char *schoolname, char *collegename, char *majorname, char *classname, char *studentname, student *data)
{
    return addnode(find(find(find(find(root, schoolname), collegename), majorname), classname), studentname, data);
}
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
void update(tree root, tree p)
{
    system("cls");
    prtree(root);
    printerface(p);
}
void cls()
{
    for (int i = 1; i < MINLINE; i++)
    {
        gotoxy(36, i);
        puts("                                                                                    ");
    }
    prhead(NULL);
}
int cat(tree p)
{
    if (!p || p->depth != 5)
        return FALSE;
    cls();
    int i = 0;
    gotoxy(50, 5 + i);
    printf(catstr[i++], p->str);
    gotoxy(50, 5 + i);
    if (p->data)
        printf(catstr[i++], p->data->sex ? "男" : "女");
    else
        printf(catstr[i++], "不详");
    gotoxy(50, 5 + i);
    if (p->data)
        printf(catstr[i++], p->data->age);
    else
        printf(catstr[i++], "不详");
    gotoxy(50, 5 + i);
    printf(catstr[i++], p->parents->parents->parents->parents->str);
    gotoxy(50, 5 + i);
    printf(catstr[i++], p->parents->parents->parents->str);
    gotoxy(50, 5 + i);
    printf(catstr[i++], p->parents->parents->str);
    gotoxy(50, 5 + i);
    printf(catstr[i++], p->parents->str);
    gotoxy(50, 5 + i);
    if (p->data)
        printf(catstr[i++], p->data->ID);
    else
        printf(catstr[i++], "不详");
    return TRUE;
}

int ls(tree p)
{
    if (!p)
        return FALSE;
    if (p->depth == 5)
        cat(p);
    else
    {
        cls();
        tree q = p->firstchild;
        int k = 0;
        while (q)
        {
            gotoxy(50, 5 + k);
            printf("%d.%s", ++k, q->str);
            q = q->nextsib;
        }
        prhead(p);
    }
    return TRUE;
}
void help()
{
    cls();

    for (int i = 0; i < 12; i++)
    {
        gotoxy(38, 2 + i);
        puts(cmdhelp[i]);
    }
}

int cd(tree *p)
{
    if (!p || !*p)
        return FALSE;
    int t;
    char a[100];
    tree tmp;
    if ((t = scanf("%s", a)) == 1)
    {

        if (!strcmp(a, "..") && (*p)->parents)
        {
            *p = (*p)->parents;
            ls(*p);
            return TRUE;
        }
        if (tmp = find(*p, a))
        {

            *p = tmp;
            ls(*p);
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
int create(tree *p, tree root)
{
    char a[100];
    if (scanf("%s", a) == 1)
    {
        if (find(*p, a))
            return FALSE;
        if (addnode(*p, a, NULL))
        {
            *p = find(*p, a);
            update(root, *p);
            ls(*p);
            return TRUE;
        }
    }
    return FALSE;
}
int lr2(tree p, int *a)
{
    if (!p)
        return FALSE;
    if (p->firstchild)
        lr2(p->firstchild, a);
    a[p->depth]++;

    if (p->nextsib)
    {
        p = p->nextsib;
        lr2(p, a);
    }
    return TRUE;
}
int lr(tree p)
{
    if (!p)
        return FALSE;
    cls();
    if (p->depth == 5)
        return FALSE;

    int a[6];
    memset(a, 0, sizeof(a));
    lr2(p->firstchild, a);

    for (int i = 5; i > p->depth; i--)
    {
        gotoxy(50, 5 + 5 - i);
        printf(lrstr[p->depth + 5 - i], a[p->depth + 5 - i + 1]);
    }
    return TRUE;
}

int main()
{
    puts("请最大化");
    {
        char ch;
        while ((ch = getchar()) != '\n')
            ;
    }
    tree root = createnode();
    root->depth = 0;
    tree p = root;
    head = (char *)malloc(100 * sizeof(char));
    strcpy(head, "root@root : ～  $ ");
    addschool(root, "杭电");
    addcollege(root, "杭电", "理学院");
    addcollege(root, "杭电", "机械学院");
    addcollege(root, "杭电", "自动化学院");
    addcollege(root, "杭电", "卓越学院");
    addcollege(root, "杭电", "材环学院");
    addcollege(root, "杭电", "计算机学院");
    addcollege(root, "杭电", "经济学院");
    addcollege(root, "杭电", "人艺数法");
    addmajor(root, "杭电", "卓越学院", "计科");
    addclass(root, "杭电", "卓越学院", "计科", "19184111");
    addclass(root, "杭电", "卓越学院", "计科", "19184112");
    addclass(root, "杭电", "卓越学院", "计科", "19184113");
    addclass(root, "杭电", "卓越学院", "计科", "19184114");
    addclass(root, "杭电", "卓越学院", "计科", "19184115");
    addstudent(root, "杭电", "卓越学院", "计科", "19184115", "张三", NULL);
    addstudent(root, "杭电", "卓越学院", "计科", "19184115", "李四", NULL);
    addstudent(root, "杭电", "卓越学院", "计科", "19184115", "王五", NULL);
    addmajor(root, "杭电", "卓越学院", "会计");
    addmajor(root, "杭电", "计算机学院", "计科");
    addmajor(root, "杭电", "计算机学院", "软工");
    addschool(root, "浙大");
    update(root, NULL);
    help();
    prhead(NULL);

    char *cmd = (char *)malloc(100 * sizeof(char));
    while (~scanf("%s", cmd) && strcmp(cmd, "exit"))
    {
        if (!strcmp(cmd, "help"))
            help();
        else if (!strcmp(cmd, "ls"))
            ls(p);
        else if (!strcmp(cmd, "cd"))
            cd(&p);
        else if (!strcmp(cmd, "create"))
            create(&p, root);
        else if (!strcmp(cmd, "addschool"))
        {
            int t;
            char a[100];
            if ((t = scanf("%s", a)) == 1)
                addschool(root, a);
            prtree(root);
        }
        else if (!strcmp(cmd, "addcollege"))
        {
            int t;
            char a[2][100];
            if ((t = scanf("%s%s", a[0], a[1])) == 2)
                addcollege(root, a[0], a[1]);
            prtree(root);
        }
        else if (!strcmp(cmd, "addmajor"))
        {
            int t;
            char a[3][100];
            if ((t = scanf("%s%s%s", a[0], a[1], a[3])) == 3)
                addmajor(root, a[0], a[1], a[3]);
            prtree(root);
        }
        else if (!strcmp(cmd, "addclass"))
        {
            int t;
            char a[4][100];
            if ((t = scanf("%s%s%s%s", a[0], a[1], a[2], a[3])) == 4)
                addclass(root, a[0], a[1], a[2], a[3]);
            prtree(root);
        }
        else if (!strcmp(cmd, "addstudent"))
        {
            int t;
            char a[5][100];
            if ((t = scanf("%s%s%s%s%s", a[0], a[1], a[2], a[3], a[4])) == 5)
                addstudent(root, a[0], a[1], a[2], a[3], a[4], NULL);
            prtree(root);
        }
        else if (!strcmp(cmd, "lr"))
        {
            int t;
            char a[100];
            if ((t = scanf("%s", a)) == 1)
            {
                if (!strcmp(a, "all"))
                    lr(root);
                else
                    lr(find(p, a));
            }
        }
        else if (!strcmp(cmd, "cat"))
        {
            int t;
            char a[100];
            if ((t = scanf("%s", a)) == 1)
                cat(find(p, a));
        }
        prhead(NULL);
    }
    system("pause");
    return 0;
}