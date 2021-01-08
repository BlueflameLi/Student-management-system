//the coding is GB2312
#include "tree.h"
#include <Windows.h>
#define MINLINE (lastline < 30 ? 30 : lastline)
char *Box_Drawings[] = {
    "└─",
    "├─",
    "│  ",
    "   "};
char *cmdhelp[20] = {"命令            功能              示例",
                     "help           查看帮助           help",
                     "exit           退出程序           exit",
                     "ls             列出子目录         ls",
                     "cd [name]      进入子目录         cd 卓越学院",
                     "cd [dir]       进入指定目录       cd /杭电/卓越学院、cd ./计科、cd ../计科",
                     "create [name]  新建               create 计算机学院",
                     "create [dir]   在指定目录新建     参考cd [dir]",
                     "rm [name]      删除               rm 卓越学院",
                     "rm [dir]       删除指定目录       参考create [dir]",
                     "lr             统计               lr",
                     "rename         修改名字           rename 杭电 杭州电子科大",
                     "modify         修改学生信息       modify 学号 "};
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
    printf("%100s\n", " ");
    printf("%100s\n", " ");
    printf("%100s\n", " ");
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
    }
    prhead(p);
    return TRUE;
}
void help()
{
    cls();

    for (int i = 0; i < 13; i++)
    {
        gotoxy(38, 2 + i);
        puts(cmdhelp[i]);
    }
}
int strcut(char *str, char *token[])
{
    token[0] = strtok(str, "/");
    int i = 0;
    while (token[i] != NULL)
        token[++i] = strtok(NULL, "/");

    return i - 1;
}
tree finddir(tree p, tree root, char *str)
{
    if (!p)
        return FALSE;

    if (!strcmp(str, ".."))
    {
        if (p->parents)
            return p->parents;
        return NULL;
    }
    if (!strcmp(str, "."))
        return p;

    if (!strncmp(str, "../", 3))
    {
        if (!p->parents)
            return NULL;
        root = p->parents;
        str += 2;
    }
    else if (!strncmp(str, "./", 2))
    {
        root = p;
        str++;
    }

    if (*str != '/')
        return find(p, str);

    tree q = root;
    char *token[6];
    str++;
    int k = strcut(str, token);
    int flag = TRUE;
    if (~k)
        for (int i = 0; i <= k; i++)
        {
            tree t;
            if (t = find(q, token[i]))
                q = t;
            else
            {
                flag = FALSE;
                break;
            }
        }
    if (flag)
        return q;
    return NULL;
}
int cd(tree *p, char *str, tree root)
{
    if (!p || !*p)
        return FALSE;
    tree q = finddir(*p, root, str);
    if (q)
    {
        *p = q;
        return TRUE;
    }
    return FALSE;
}
int create(tree *p, char *str, tree root)
{

    char *tmp = strrchr(str, '/');

    if (!tmp)
    {
        if (!find(*p, str) && addnode(*p, str, NULL))
        {
            return TRUE;
        }
        return FALSE;
    }

    if (tmp == str)
        str = "/";
    else
        *tmp = '\0';
    tmp++;

    tree q;
    if (q = finddir(*p, root, str))
    {
        if (!find(q, tmp) && addnode(q, tmp, NULL))
        {
            *p = q;
            return TRUE;
        }
        return FALSE;
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

int rm(tree *p, char *str, tree root)
{
    if (!p && !*p)
        return FALSE;
    tree q;
    if ((q = finddir(*p, root, str)) && q->parents)
    {
        *p = q->parents;
        if (q == q->parents->firstchild)
        {
            q->parents->firstchild = q->nextsib;
        }
        else
        {
            tree tmp = q->parents->firstchild;
            while (tmp->nextsib)
            {
                if (tmp->nextsib == q)
                {
                    tmp->nextsib = q->nextsib;
                    break;
                }
                tmp = tmp->nextsib;
            }
        }
        return TRUE;
    }
    return FALSE;
}
int renme(tree p, char *name1, char *name2)
{
    if (!p)
        return FALSE;
    p = find(p, name1);
    if (p)
    {
        strcpy(p->str, name2);
        return TRUE;
    }
    return FALSE;
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
    while (gets(cmd) && strcmp(cmd, "exit"))
    {
        if (!strcmp(cmd, "help"))
            help();
        else if (!strcmp(cmd, "ls"))
            ls(p);
        else if (!strncmp(cmd, "cd ", 3))
        {
            char *tmp = cmd + 3;
            while (*tmp == ' ')
                tmp++;
            if (*tmp && cd(&p, tmp, root))
                ls(p);
        }
        else if (!strncmp(cmd, "create ", 7))
        {
            char *tmp = cmd + 7;
            while (*tmp == ' ')
                tmp++;
            if (*tmp && create(&p, tmp, root))
            {
                update(root, p);
                ls(p);
            }
        }
        else if (!strcmp(cmd, "lr"))
            lr(p);
        else if (!strncmp(cmd, "rm ", 3))
        {
            char *tmp = cmd + 3;
            while (*tmp == ' ')
                tmp++;
            if (*tmp && rm(&p, tmp, root))
            {
                update(root, p);
                ls(p);
            }
        }
        prhead(NULL);
    }
    system("pause");
    return 0;
}