//the coding is GB2312
#include "tree.h"
#include <Windows.h>

char *Box_Drawings[] = {
    "����",
    "����",
    "��  ",
    "    "};
char *cmdhelp[] = {"help       �鿴����",
                   "exit       �˳�����",
                   "ls         �г���Ŀ¼"};
int lastline;
char *head;
//����ƶ�
void gotoxy(unsigned char x, unsigned char y)
{
    //COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
    COORD cor;

    //���
    HANDLE hout;

    //�趨����Ҫ��λ��������
    cor.X = x;
    cor.Y = y;

    //GetStdHandle������ȡһ��ָ���ض���׼�豸�ľ����������׼���룬��׼����ͱ�׼����
    //STD_OUTPUT_HANDLE���Ǵ����׼�����Ҳ������ʾ�����ĺ�
    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    //SetConsoleCursorPosition�����������ÿ���̨����λ��
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
        strcpy(head, "root@root : �� ");
        prfa(p);
        strcat(head, " $ ");
    }
    gotoxy(0, lastline + 1);
    printf("%50s\r", " ");
    printf("%s", head);
}
void printerface()
{
    gotoxy(0, 0);
    puts("*********************************************************ѧ������ϵͳ********************************");
    for (int i = 1; i < lastline; i++)
    {
        gotoxy(25, i);
        putchar('*');
        gotoxy(100, i);
        putchar('*');
    }
    gotoxy(0, lastline);
    puts("*****************************************************************************************************");
    gotoxy(105, 0);
    puts("help��ȡ����");
    prhead(NULL);
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
        lastline++;
        int flag4 = q->nextsib ? 1 : 0;
        printf("*%4s%4s%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2 ? 2 : 3], Box_Drawings[flag3 ? 2 : 3], Box_Drawings[flag4], q->str);
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
        lastline++;
        int flag3 = q->nextsib ? 1 : 0;
        printf("*%4s%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2 ? 2 : 3], Box_Drawings[flag3], q->str);
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
        lastline++;
        int flag2 = q->nextsib ? 1 : 0;
        printf("*%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2], q->str);
        prclass(q, flag1, flag2);
        q = q->nextsib;
    }
}
int prschool(tree root)
{
    gotoxy(0, 1);
    lastline = 1;
    if (!root)
        return FALSE;
    tree p = root->firstchild;
    while (p)
    {
        lastline++;
        int flag = p->nextsib ? 1 : 0;
        printf("*%s %s\n", Box_Drawings[flag], p->str);
        prcollege(p, flag);
        p = p->nextsib;
    }
}


void cls()
{
    for (int i = 1; i < lastline; i++)
    {
        gotoxy(26, i);
        puts("                                                                          ");
    }
    prhead(NULL);
}

int update(tree p)
{
    if (!p)
        return FALSE;
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
    return TRUE;
}
void help()
{
    cls();

    for (int i = 0; i < 3; i++)
    {
        gotoxy(50, 5 + i);
        puts(cmdhelp[i]);
    }
}
int main()
{
    tree root = createnode();
    tree p = root;
    head = (char *)malloc(100 * sizeof(char));
    strcpy(head, "root@root : ��  $ ");
    addschool(root, "����");
    addcollege(root, "����", "��ѧԺ");
    addcollege(root, "����", "��еѧԺ");
    addcollege(root, "����", "�Զ���ѧԺ");
    addcollege(root, "����", "׿ԽѧԺ");
    addcollege(root, "����", "�Ļ�ѧԺ");
    addcollege(root, "����", "�����ѧԺ");
    addcollege(root, "����", "����ѧԺ");
    addcollege(root, "����", "��������");
    addclass(root, "����", "׿ԽѧԺ", "19184111");
    addclass(root, "����", "׿ԽѧԺ", "19184112");
    addclass(root, "����", "׿ԽѧԺ", "19184113");
    addclass(root, "����", "׿ԽѧԺ", "19184114");
    addclass(root, "����", "׿ԽѧԺ", "19184115");
    addstudent(root, "����", "׿ԽѧԺ", "19184115", "����", NULL);
    addstudent(root, "����", "׿ԽѧԺ", "19184115", "����", NULL);
    addstudent(root, "����", "׿ԽѧԺ", "19184115", "����", NULL);
    addschool(root, "���");
    prschool(root);
    printerface();
    // cls();
    // update(root);
    help();
    prhead(NULL);
    // printf("%s %s\n", Box_Drawings[0], "����");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "��ѧԺ");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "��еѧԺ");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "�Զ���ѧԺ");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "׿ԽѧԺ");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184111");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184112");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184113");
    // printf("%4s%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[2], Box_Drawings[1], "����");
    // printf("%4s%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[2], Box_Drawings[1], "����");
    // printf("%4s%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[2], Box_Drawings[0], "����");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[1], "19184114");
    // printf("%4s%4s%4s %s\n", Box_Drawings[3], Box_Drawings[2], Box_Drawings[0], "19184115");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "�Ļ�ѧԺ");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "�����ѧԺ");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[1], "����ѧԺ");
    // printf("%4s%4s %s\n", Box_Drawings[3], Box_Drawings[0], "��������");

    char *cmd = (char *)malloc(100 * sizeof(char));
    while (~scanf("%s", cmd) && strcmp(cmd, "exit"))
    {
        if (!strcmp(cmd, "help"))
            help();
        else if (!strcmp(cmd, "ls"))
            update(p);
        prhead(NULL);
    }
    system("pause");
    return 0;
}