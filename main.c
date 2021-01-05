//the coding is GB2312
#include "tree.h"
#include <Windows.h>
#define MINLINE (lastline < 30 ? 30 : lastline)
char *Box_Drawings[] = {
    "����",
    "����",
    "��  ",
    "   "};
char *cmdhelp[20] = {"����              ����              ʾ��",
                     "help             �鿴����           help",
                     "exit             �˳�����           exit",
                     "ls               �г���Ŀ¼         ls",
                     "cd               �л�Ŀ¼           cd ���硢cd ..",
                     "create           �½�Ŀ¼           create �����ѧԺ",
                     "addschool        ����ѧУ           addschool ����",
                     "addcollege       ����ѧԺ           addcollege ���� ׿ԽѧԺ",
                     "addmajor         ����רҵ           addmajor ���� ׿ԽѧԺ �ƿ�",
                     "addclass         �����༶           addclass ���� ׿ԽѧԺ �ƿ� 19184115",
                     "addstudent       ����ѧ��           addstudent ���� ׿ԽѧԺ �ƿ� 19184115 ����",
                     "lr               ͳ��               lr ׿ԽѧԺ��lr all"};
int lastline;
char *head;
char *lrstr[5] = {
    "����%d��ѧУ",
    "����%d��ѧԺ",
    "����%d��רҵ",
    "����%d���༶",
    "����%d��ѧ��"};
char *catstr[10] = {"������%s", "�Ա�%s", "���䣺%s", "ѧУ��%s", "ѧԺ��%s", "רҵ��%s", "�༶��%s", "ѧ�ţ�%s"};
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
    puts("*******************************************************************ѧ������ϵͳ******************************************");
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
        printf(catstr[i++], p->data->sex ? "��" : "Ů");
    else
        printf(catstr[i++], "����");
    gotoxy(50, 5 + i);
    if (p->data)
        printf(catstr[i++], p->data->age);
    else
        printf(catstr[i++], "����");
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
        printf(catstr[i++], "����");
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
    puts("�����");
    {
        char ch;
        while ((ch = getchar()) != '\n')
            ;
    }
    tree root = createnode();
    root->depth = 0;
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