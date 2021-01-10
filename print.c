//the coding is GB2312

#include "print.h"

//���������ַ�
char *Box_Drawings[4] = {
    "����",
    "����",
    "��  ",
    "   "};

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

//��ӡ��ǰ·��
int prfa(tree p)
{
    if (!p->parents)
        return FALSE;
    prfa(p->parents);
    strcat(head, "/");
    strcat(head, p->str);
}

//��ӡ�û�ͷ
void prhead(tree p)
{

    if (p)
    {
        strcpy(head, "root@root : �� ");
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

//��ӡ����
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

//�ݹ��ӡĿ¼��
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

//��ӡĿ¼��
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

//����Ҳ���ʾ��
void cls()
{
    for (int i = 1; i < MINLINE; i++)
    {
        gotoxy(36, i);
        puts("                                                                                    ");
    }
    prhead(NULL);
}