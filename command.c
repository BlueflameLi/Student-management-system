#include "command.h"
//�������
char *cmdhelp[20] = {"����                 ����              ʾ��",
                     "help                �鿴����           help",
                     "exit                �˳�����           exit",
                     "ls                  �г���Ŀ¼         ls",
                     "cd [name]           ������Ŀ¼         cd ׿ԽѧԺ",
                     "cd [dir]            ����ָ��Ŀ¼       cd /����/׿ԽѧԺ��cd ./�ƿơ�cd ../�ƿ�",
                     "create [name]       �½�               create �����ѧԺ",
                     "create [dir]        ��ָ��Ŀ¼�½�     �ο�cd [dir]",
                     "rm [name]           ɾ��               rm ׿ԽѧԺ",
                     "rm [dir]            ɾ��ָ��Ŀ¼       �ο�create [dir]",
                     "lr                  ͳ��               lr",
                     "rename [newname]    ��ǰĿ¼������     rename ���ݵ��ӿƴ�",
                     "modify [parm] [str] �޸�ѧ����Ϣ       modify -n ���� -id 19180101",
                     "modify -help        �鿴modify����     modify -help",
                     "mv [dir] [dir]      ѧ��תѧ��         mv ./19184115/���� ../���/19184211",
                     "find [parm] [str]   ����ѧ��           find  -college �����ѧԺ -n ����",
                     "find -help          �鿴find����       find -help",
                     "undo                ����               undo"};

//modify����
char *modifyhelp[10] = {
    "����                 ����              ʾ��",
    "modify -n [name]  �޸�ѧ������         modify -n ����",
    "modify -id [id]   �޸�ѧ��ѧ��         modify -id 19180101",
    "modify -sex [sex] �޸�ѧ���Ա�         modify -sex ��",
    "modify -age [age] �޸�ѧ������         modify -age 18",
    "modify -help      �鿴modify����       modify -help",
    "ע����help�����⣬�����������������ʹ��,����modify -n ���� -sex Ů -age 18"};

//find����
char *findhelp[15] = {
    "����                 ����              ʾ��",
    "find -n [name]     ����������          find -n ����",
    "find -id [id]      ��ѧ�Ų���          find -id 19180101",
    "find -sex [sex]    ���Ա����          find -sex ��",
    "find -age [age]    ���������          find -age 18",
    "find -sch [name]   ��ѧУ����          find -sch ����",
    "find -colg [name]  ��ѧԺ����          find -colg �����ѧԺ",
    "find -maj [name]   ��רҵ����          find -maj �ƿ�",
    "find -class [name] ���༶����          find -class 19184111",
    "find -help         �鿴modify����       modify -help",
    "ע��1.����Ĭ�ϴӵ�ǰĿ¼����,����ȫ�ֲ����������Ӳ���-all",
    "    2.ѧ�š��Ա���������Ϊ��ȷƥ�䣬�������ҷ�ʽΪ��ȷ����",
    "    3.��help��all�����⣬�����������������ʹ��,����find -n ���� -sex Ů -age 18"};

//lr��ʾ������
char *lrstr[5] = {
    "����%d��ѧУ",
    "����%d��ѧԺ",
    "����%d��רҵ",
    "����%d���༶",
    "����%d��ѧ��"};

//Ŀǰ��ȥ�������������ڲ���
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

//��ʾѧ����Ϣ
int cat(tree p)
{
    if (!p || p->depth != 5)
        return FALSE;

    //�����Ļ
    cls();

    //��ӡ��Ϣ
    gotoxy(50, 5);
    printf("������%s", p->str);

    gotoxy(50, 5 + 1);
    if (p->data && ~p->data->sex)
        printf("�Ա�%s", p->data->sex ? "��" : "Ů");
    else
        printf("�Ա�%s", "����");

    gotoxy(50, 5 + 2);
    if (p->data && ~p->data->age)
        printf("���䣺%d", p->data->age);
    else
        printf("���䣺%s", "����");

    gotoxy(50, 5 + 3);
    printf("ѧУ��%s", p->parents->parents->parents->parents->str);

    gotoxy(50, 5 + 4);
    printf("ѧԺ��%s", p->parents->parents->parents->str);

    gotoxy(50, 5 + 5);
    printf("רҵ��%s", p->parents->parents->str);

    gotoxy(50, 5 + 6);
    printf("�༶��%s", p->parents->str);

    gotoxy(50, 5 + 7);
    if (p->data && ~p->data->ID)
        printf("ѧ�ţ�%d", p->data->ID);
    else
        printf("ѧ�ţ�%s", "����");

    return TRUE;
}

//��ʾ��Ŀ¼
int ls(tree p)
{
    if (!p)
        return FALSE;

    //��ǰĿ¼��ѧ���Ļ�����ʾѧ����Ϣ
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

//���½���
void update(tree root, tree p)
{
    system("cls");
    prtree(root);
    printerface(p);
    ls(p);
}

//�鿴����
void help()
{
    cls();

    for (int i = 0; i < 18; i++)
    {
        gotoxy(38, 2 + i);
        puts(cmdhelp[i]);
    }
}

//�ַ����ָ�
int strcut(char *str, char *token[], char *delim)
{
    token[0] = strtok(str, delim);
    int i = 0;
    while (token[i] != NULL)
        token[++i] = strtok(NULL, delim);

    return i - 1;
}

//����·��
tree finddir(tree p, tree root, char *str)
{
    if (!p)
        return FALSE;

    //��Ŀ¼
    if (!strcmp(str, ".."))
    {
        if (p->parents)
            return p->parents;
        return NULL;
    }

    //��ǰĿ¼
    if (!strcmp(str, "."))
        return p;

    //�Ӹ�Ŀ¼��ʼ��·��
    if (!strncmp(str, "../", 3))
    {
        if (!p->parents)
            return NULL;
        root = p->parents;
        str += 2;
    }
    else if (!strncmp(str, "./", 2)) //�ӵ�ǰĿ¼��ʼ��·��
    {
        root = p;
        str++;
    }

    //��·����ֱ��������Ŀ¼
    if (*str != '/')
        return find(p, str);

    tree q = root;
    char *token[6];
    str++;
    int k = strcut(str, token, "/");
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

//�л�Ŀ¼
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

//������Ŀ¼
int create(tree *p, char *str, tree root)
{

    char *tmp = strrchr(str, '/');

    if (!tmp)
    {
        if (!find(*p, str) && addnode(*p, str, NULL))
        {
            unit u;
            u.cmd = 1;
            u.data = find(*p, str);
            u.data2 = NULL;
            u.str = NULL;
            push(&undoStack, u);

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
            unit u;
            u.cmd = 1;
            u.data = find(q, tmp);
            u.data2 = NULL;
            u.str = NULL;
            push(&undoStack, u);

            *p = q;
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

//�ݹ�ͳ��
int lr2(tree p, int *cnt)
{
    if (!p)
        return FALSE;

    if (p->firstchild)
        lr2(p->firstchild, cnt);

    cnt[p->depth]++;

    if (p->nextsib)
    {
        p = p->nextsib;
        lr2(p, cnt);
    }

    return TRUE;
}

//ͳ��
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

//ɾ��Ŀ¼
int rm(tree *p, char *str, tree root)
{
    if (!p && !*p)
        return FALSE;

    tree q;
    if ((q = finddir(*p, root, str)) && q->parents)
    {
        *p = q->parents;
        if (q == q->parents->firstchild)
            q->parents->firstchild = q->nextsib;
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

        unit u;
        u.cmd = 2;
        u.data = q;
        u.data2 = NULL;
        u.str = NULL;
        push(&undoStack, u);

        return TRUE;
    }

    return FALSE;
}

//������
int renme(tree p, char *newname)
{
    if (!p || !newname)
        return FALSE;

    unit u;
    u.cmd = 3;
    u.data = p;
    u.data2 = NULL;
    u.str = (char *)malloc(100 * sizeof(char));
    strcpy(u.str, p->str);
    push(&undoStack, u);

    strcpy(p->str, newname);

    return TRUE;
}

//�޸�ѧ����Ϣ
int modify(tree p, char *str)
{
    if (!p || p->depth != 5)
        return FALSE;
    if (*str != '-')
        return FALSE;

    char *token[10];
    int k = strcut(str, token, " ");

    if (k > 0 && k % 2)
    {
        int flag = 0;
        char *name = NULL;
        int id = -1, sex = -1, age = -1;
        for (int i = 0; i <= k; i += 2)
        {
            if (!strcmp(token[i], "-n"))
            {
                if (token[i + 1][0] == '-')
                {
                    flag = 1;
                    break;
                }
                name = token[i + 1];
            }
            else if (!strcmp(token[i], "-sex"))
            {
                if (!strcmp(token[i + 1], "��"))
                    sex = M;
                else if (!strcmp(token[i + 1], "Ů"))
                    sex = F;
                else
                {
                    flag = 2;
                    break;
                }
            }
            else if (!strcmp(token[i], "-age"))
            {
                if (!(age = atoi(token[i + 1])))
                {
                    flag = 3;
                    break;
                }
            }
            else if (!strcmp(token[i], "-id"))
            {
                if (!(id = atoi(token[i + 1])))
                {
                    flag = 4;
                    break;
                }
            }
            else
            {
                flag = 5;
                break;
            }
        }

        if (flag)
            return FALSE;

        unit u;
        u.cmd = 4;
        u.data = p;
        u.data2 = NULL;
        if (p->data)
            u.stu = *(p->data);
        else
            u.stu.age = u.stu.ID = u.stu.sex = -1;

        if (name)
        {
            u.str = (char *)malloc(100 * sizeof(char));
            strcpy(u.str, p->str);
            strcpy(p->str, name);
        }
        else
            u.str = NULL;

        if (~sex || ~age || ~id)
        {
            if (!p->data)
            {
                p->data = (student *)malloc(sizeof(student));
                p->data->age = p->data->ID = p->data->sex = -1;
            }

            if (~sex)
                p->data->sex = sex;
            if (~age)
                p->data->age = age;
            if (~id)
                p->data->ID = id;
        }

        push(&undoStack, u);

        return TRUE;
    }
    return FALSE;
}

//�ƶ�ѧ��
int mv(tree p, tree root, char *str)
{
    if (!p)
        return FALSE;

    char *token[10];
    int k = strcut(str, token, " ");

    if (k == 1)
    {
        tree p1, p2;
        if ((p1 = finddir(p, root, token[0])) && p1->depth == 5 && (p2 = finddir(p, root, token[1])) && p2->depth == 4)
        {
            if (p1 == p1->parents->firstchild)
                p1->parents->firstchild = p1->nextsib;
            else
            {
                tree tmp = p1->parents->firstchild;
                while (tmp->nextsib)
                {
                    if (tmp->nextsib == p1)
                    {
                        tmp->nextsib = p1->nextsib;
                        break;
                    }
                    tmp = tmp->nextsib;
                }
            }

            unit u;
            u.cmd = 5;
            u.data = createnode();
            *u.data = *p1;
            u.data2 = p2;
            u.str = NULL;
            push(&undoStack, u);

            p1->parents = p2;
            p1->nextsib = NULL;

            if (!p2->firstchild)
                p2->firstchild = p1;
            else
            {
                tree tmp = p2->firstchild;
                while (tmp->nextsib)
                    tmp = tmp->nextsib;
                tmp->nextsib = p1;
            }
        }
        return TRUE;
    }

    return FALSE;
}

//�ݹ�����
int search2(tree p, char *str[], int id, int sex, int age, tree *list, int *k)
{
    if (!p)
        return FALSE;

    if (p->depth < 5)
    {
        if (p->firstchild)
        {
            if (!str[p->depth] || strstr(p->firstchild->str, str[p->depth]))
                search2(p->firstchild, str, id, sex, age, list, k);
            p = p->firstchild;

            while (p->nextsib)
            {
                if (!str[p->depth - 1] || strstr(p->nextsib->str, str[p->depth - 1]))
                    search2(p->nextsib, str, id, sex, age, list, k);
                p = p->nextsib;
            }
            return TRUE;
        }
        return FALSE;
    }

    if (p->depth == 5)
    {

        if (~id || ~sex || ~age)
        {
            if (!p->data)
                return FALSE;
            if (~id && p->data->ID != id)
                return FALSE;
            if (~sex && p->data->sex != sex)
                return FALSE;
            if (~age && p->data->age != age)
                return FALSE;
        }

        list[(*k)++] = p;
        return TRUE;
    }
}

//����
int search(tree p, tree root, char *str)
{
    if (!p)
        return FALSE;
    if (*str != '-')
        return FALSE;

    char *token[10];
    int k = strcut(str, token, " ");

    if (k > 0)
    {
        if (k % 2 == 0)
        {
            if (!strcmp(token[k--], "-all"))
                p = root;
            else
                return FALSE;
        }

        int flag = 0;
        char *str[5];
        for (int i = 0; i < 5; i++)
            str[i] = NULL;
        int id = -1, age = -1, sex = -1;

        for (int i = 0; i <= k; i += 2)
        {
            if (!strcmp(token[i], "-n"))
            {
                if (token[i + 1][0] == '-')
                {
                    flag = 1;
                    break;
                }
                if (p->depth == 5)
                {
                    tree q = p;
                    if (!strstr(q->str, token[i + 1]))
                    {
                        flag = 13;
                        break;
                    }
                }
                str[4] = token[i + 1];
            }
            else if (!strcmp(token[i], "-sex"))
            {
                if (!strcmp(token[i + 1], "��"))
                    sex = M;
                else if (!strcmp(token[i + 1], "Ů"))
                    sex = F;
                else
                {
                    flag = 2;
                    break;
                }
            }
            else if (!strcmp(token[i], "-age"))
            {
                if (!(age = atoi(token[i + 1])))
                {
                    flag = 3;
                    break;
                }
            }
            else if (!strcmp(token[i], "-id"))
            {
                if (!(id = atoi(token[i + 1])))
                {
                    flag = 4;
                    break;
                }
            }
            else if (!strcmp(token[i], "-sch"))
            {
                if (token[i + 1][0] == '-')
                {
                    flag = 5;
                    break;
                }
                if (p != root)
                {
                    tree q = p;
                    while (q->depth > 1)
                        q = q->parents;
                    if (!strstr(q->str, token[i + 1]))
                    {
                        flag = 10;
                        break;
                    }
                }
                str[0] = token[i + 1];
            }
            else if (!strcmp(token[i], "-colg"))
            {
                if (token[i + 1][0] == '-')
                {
                    flag = 6;
                    break;
                }
                if (p->depth >= 2)
                {
                    tree q = p;
                    while (q->depth > 2)
                        q = q->parents;
                    if (!strstr(q->str, token[i + 1]))
                    {
                        flag = 11;
                        break;
                    }
                }
                str[1] = token[i + 1];
            }
            else if (!strcmp(token[i], "-maj"))
            {
                if (token[i + 1][0] == '-')
                {
                    flag = 7;
                    break;
                }
                if (p->depth >= 3)
                {
                    tree q = p;
                    while (q->depth > 3)
                        q = q->parents;
                    if (!strstr(q->str, token[i + 1]))
                    {
                        flag = 12;
                        break;
                    }
                }
                str[2] = token[i + 1];
            }
            else if (!strcmp(token[i], "-class"))
            {
                if (token[i + 1][0] == '-')
                {
                    flag = 8;
                    break;
                }
                if (p->depth >= 4)
                {
                    tree q = p;
                    while (q->depth > 4)
                        q = q->parents;
                    if (!strstr(q->str, token[i + 1]))
                    {
                        flag = 13;
                        break;
                    }
                }
                str[3] = token[i + 1];
            }
            else
            {
                flag = 9;
                break;
            }
        }

        if (flag)
            return FALSE;

        tree list[100];
        k = 0;

        search2(p, str, id, sex, age, list, &k);

        cls();
        gotoxy(38, 2);
        printf("��������%d����¼", k);

        gotoxy(38, 3);
        printf("%-10s%-10s%-10s%-10s%-10s%s", "����", "ѧУ", "ѧԺ", "רҵ", "�༶", "ѧ��");

        for (int i = 0; i < k; i++)
        {
            gotoxy(38, 4 + i);
            printf("%-10s%-10s%-10s%-10s%-10s", list[i]->str, list[i]->parents->parents->parents->parents->str, list[i]->parents->parents->parents->str, list[i]->parents->parents->str, list[i]->parents->str);
            if (list[i]->data && ~list[i]->data->ID)
                printf("%d", list[i]->data->ID);
            else
                printf("%s", "����");
        }
        return TRUE;
    }
    return FALSE;
}

//����
int undo()
{
    if (!StackEmpty(&undoStack))
    {
        unit u = *gettop(&undoStack);
        pop(&undoStack);
        if (u.cmd == 1)
        {
            if (u.data == u.data->parents->firstchild)
                u.data->parents->firstchild = u.data->nextsib;
            else
            {
                tree p = u.data->parents->firstchild;
                while (p->nextsib && p->nextsib != u.data)
                    p = p->nextsib;
                if (p->nextsib)
                    p->nextsib = u.data->nextsib;
            }
            free(u.data);
        }
        else if (u.cmd == 2)
        {
            if (!u.data->parents->firstchild || u.data->parents->firstchild == u.data->nextsib)
                u.data->parents->firstchild = u.data;
            else
            {
                tree p = u.data->parents->firstchild;
                while (p->nextsib && p->nextsib != u.data->nextsib)
                    p = p->nextsib;
                p->nextsib = u.data;
            }
        }
        else if (u.cmd == 3)
        {
            strcpy(u.data->str, u.str);
            free(u.str);
        }
        else if (u.cmd == 4)
        {
            if (u.data->data)
                *(u.data->data) = u.stu;
            if (u.str)
            {
                strcpy(u.data->str, u.str);
                free(u.str);
            }
        }
        else if (u.cmd == 5)
        {
            tree p = u.data2->firstchild;
            while (p->nextsib && p->nextsib->nextsib)
                p = p->nextsib;
            if (p->nextsib)
            {
                free(p->nextsib);
                p->nextsib = NULL;
            }
            else
            {
                free(p);
                u.data2->firstchild = NULL;
            }

            if (!u.data->parents->firstchild || u.data->parents->firstchild == u.data->nextsib)
                u.data->parents->firstchild = u.data;
            else
            {
                tree p = u.data->parents->firstchild;
                while (p->nextsib && p->nextsib != u.data->nextsib)
                    p = p->nextsib;
                p->nextsib = u.data;
            }
        }
        else
            return FALSE;

        return TRUE;
    }
    return FALSE;
}