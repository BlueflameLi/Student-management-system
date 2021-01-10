//the coding is GB2312
#include "command.h"

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
    InitStack(&undoStack);

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
                update(root, p);
        }
        else if (!strncmp(cmd, "rm ", 3))
        {
            char *tmp = cmd + 3;
            while (*tmp == ' ')
                tmp++;
            if (*tmp && rm(&p, tmp, root))
                update(root, p);
        }
        else if (!strcmp(cmd, "lr"))
            lr(p);
        else if (!strncmp(cmd, "rename ", 7))
        {
            char *tmp = cmd + 7;
            while (*tmp == ' ')
                tmp++;
            if (*tmp && p != root && renme(p, tmp))
                update(root, p);
        }
        else if (!strncmp(cmd, "modify ", 7))
        {
            char *tmp = cmd + 7;
            while (*tmp == ' ')
                tmp++;
            if (!strcmp(tmp, "-help"))
            {
                cls();
                for (int i = 0; i < 7; i++)
                {
                    gotoxy(38, 5 + i);
                    puts(modifyhelp[i]);
                }
            }
            else if (*tmp && modify(p, tmp))
                update(root, p);
        }
        else if (!strncmp(cmd, "mv ", 3))
        {
            char *tmp = cmd + 3;
            while (*tmp == ' ')
                tmp++;
            if (*tmp && mv(p, root, tmp))
                update(root, p);
        }
        else if (!strncmp(cmd, "find ", 5))
        {
            char *tmp = cmd + 5;
            while (*tmp == ' ')
                tmp++;
            if (!strcmp(tmp, "-help"))
            {
                cls();
                for (int i = 0; i < 13; i++)
                {
                    gotoxy(38, 5 + i);
                    puts(findhelp[i]);
                }
            }
            else if (*tmp)
                search(p, root, tmp);
        }
        else if (!strcmp(cmd, "undo"))
            if (undo())
                update(root, p);
        prhead(NULL);
    }
    system("pause");
    return 0;
}