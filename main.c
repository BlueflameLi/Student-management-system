//the coding is GB2312
#include "tree.h"
#include <Windows.h>

char *Box_Drawings[] = {
    "����",
    "����",
    "��  ",
    "    "};
char *cmdhelp[20] = {"����              ����                 ʾ��",
                     "help             �鿴����              help",
                     "exit             �˳�����              exit",
                     "ls               �г���Ŀ¼            ls",
                     "cd               �л�Ŀ¼              cd ���硢cd ..",
                     "create           �ڵ�ǰĿ¼������Ŀ¼   create �����ѧԺ",
                     "addschool        ����ѧУ              addschool ����",
                     "addcollege       ����ѧԺ              addcollege ���� ׿ԽѧԺ",
                     "addmajor         ����רҵ              addmajor ���� ׿ԽѧԺ �ƿ�",
                     "addclass         �����༶              addclass ���� ׿ԽѧԺ �ƿ� 19184115",
                     "addstudent       ����ѧ��              addstudent ���� ׿ԽѧԺ �ƿ� 19184115 ����"};
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
    printf("%80s\r", " ");
    printf("%s", head);
}
void printerface(tree p)
{
    gotoxy(0, 0);
    puts("*******************************************************************ѧ������ϵͳ******************************************");
    for (int i = 1; i < lastline; i++)
    {
        gotoxy(35, i);
        putchar('*');
        gotoxy(120, i);
        putchar('*');
    }
    gotoxy(0, lastline);
    puts("*************************************************************************************************************************");
    gotoxy(125, 0);
    puts("help��ȡ����");
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
int prtree(tree p)
{
    if (!p)
        return FALSE;
    puts(p->str);
    prtree(p->nextsib);
    prtree(p->firstchild);
    return TRUE;
}
int prstudent(tree p, int flag1, int flag2, int flag3, int flag4)
{
    if (!p)
        return FALSE;
    tree q = p->firstchild;
    while (q)
    {
        lastline++;
        int flag5 = q->nextsib ? 1 : 0;
        printf("*%4s%4s%4s%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2 ? 2 : 3], Box_Drawings[flag3 ? 2 : 3], Box_Drawings[flag4 ? 2 : 3], Box_Drawings[flag5], q->str);
        q = q->nextsib;
    }
}
int prclass(tree p, int flag1, int flag2, int flag3)
{
    if (!p)
        return FALSE;
    tree q = p->firstchild;
    while (q)
    {
        lastline++;
        int flag4 = q->nextsib ? 1 : 0;
        printf("*%4s%4s%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2 ? 2 : 3], Box_Drawings[flag3 ? 2 : 3], Box_Drawings[flag4], q->str);
        prstudent(q, flag1, flag2, flag3, flag4);
        q = q->nextsib;
    }
}
int prmajor(tree p, int flag1, int flag2)
{
    if (!p)
        return FALSE;
    tree q = p->firstchild;
    while (q)
    {
        lastline++;
        int flag3 = q->nextsib ? 1 : 0;
        printf("*%4s%4s%4s %s\n", Box_Drawings[flag1 ? 2 : 3], Box_Drawings[flag2 ? 2 : 3], Box_Drawings[flag3], q->str);
        prclass(q, flag1, flag2, flag3);
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
        prmajor(q, flag1, flag2);
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
void update(tree root, tree p)
{
    system("cls");
    prschool(root);
    printerface(p);
}
void cls()
{
    for (int i = 1; i < lastline; i++)
    {
        gotoxy(36, i);
        puts("                                                                                    ");
    }
    prhead(NULL);
}

int ls(tree p)
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

    for (int i = 0; i < 11; i++)
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
        if (addnode(*p, a, NULL))
        {
            *p = find(*p, a);
            update(root, *p);
            ls(*p);
            return TRUE;
        }
    return FALSE;
}
int main()
{
    puts("�����");
    {
        char ch;
        while ((ch = getchar()) != '\n')
            ;
    }
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
    addmajor(root, "����", "׿ԽѧԺ", "�ƿ�");
    addclass(root, "����", "׿ԽѧԺ", "�ƿ�", "19184111");
    addclass(root, "����", "׿ԽѧԺ", "�ƿ�", "19184112");
    addclass(root, "����", "׿ԽѧԺ", "�ƿ�", "19184113");
    addclass(root, "����", "׿ԽѧԺ", "�ƿ�", "19184114");
    addclass(root, "����", "׿ԽѧԺ", "�ƿ�", "19184115");
    addstudent(root, "����", "׿ԽѧԺ", "�ƿ�", "19184115", "����", NULL);
    addstudent(root, "����", "׿ԽѧԺ", "�ƿ�", "19184115", "����", NULL);
    addstudent(root, "����", "׿ԽѧԺ", "�ƿ�", "19184115", "����", NULL);
    addmajor(root, "����", "׿ԽѧԺ", "���");
    addmajor(root, "����", "�����ѧԺ", "�ƿ�");
    addmajor(root, "����", "�����ѧԺ", "��");
    addschool(root, "���");
    prschool(root);
    printerface(NULL);
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
            ls(p);
        else if (!strcmp(cmd, "cd"))
            cd(&p);
        else if (!strcmp(cmd, "create"))
            create(&p, root);
        prhead(NULL);
    }
    system("pause");
    return 0;
}