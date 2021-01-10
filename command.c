#include "command.h"
//命令帮助
char *cmdhelp[20] = {"命令                 功能              示例",
                     "help                查看帮助           help",
                     "exit                退出程序           exit",
                     "ls                  列出子目录         ls",
                     "cd [name]           进入子目录         cd 卓越学院",
                     "cd [dir]            进入指定目录       cd /杭电/卓越学院、cd ./计科、cd ../计科",
                     "create [name]       新建               create 计算机学院",
                     "create [dir]        在指定目录新建     参考cd [dir]",
                     "rm [name]           删除               rm 卓越学院",
                     "rm [dir]            删除指定目录       参考create [dir]",
                     "lr                  统计               lr",
                     "rename [newname]    当前目录重命名     rename 杭州电子科大",
                     "modify [parm] [str] 修改学生信息       modify -n 张三 -id 19180101",
                     "modify -help        查看modify帮助     modify -help",
                     "mv [dir] [dir]      学生转学籍         mv ./19184115/张三 ../会计/19184211",
                     "find [parm] [str]   查找学生           find  -college 计算机学院 -n 张三",
                     "find -help          查看find帮助       find -help",
                     "undo                撤销               undo"};

//modify帮助
char *modifyhelp[10] = {
    "命令                 功能              示例",
    "modify -n [name]  修改学生姓名         modify -n 张三",
    "modify -id [id]   修改学生学号         modify -id 19180101",
    "modify -sex [sex] 修改学生性别         modify -sex 男",
    "modify -age [age] 修改学生年龄         modify -age 18",
    "modify -help      查看modify帮助       modify -help",
    "注：除help参数外，其他参数可任意组合使用,例如modify -n 张三 -sex 女 -age 18"};

//find帮助
char *findhelp[15] = {
    "命令                 功能              示例",
    "find -n [name]     按姓名查找          find -n 张三",
    "find -id [id]      按学号查找          find -id 19180101",
    "find -sex [sex]    按性别查找          find -sex 男",
    "find -age [age]    按年龄查找          find -age 18",
    "find -sch [name]   按学校查找          find -sch 杭电",
    "find -colg [name]  按学院查找          find -colg 计算机学院",
    "find -maj [name]   按专业查找          find -maj 计科",
    "find -class [name] 按班级查找          find -class 19184111",
    "find -help         查看modify帮助       modify -help",
    "注：1.查找默认从当前目录查找,如需全局查请在最后添加参数-all",
    "    2.学号、性别和年龄查找为精确匹配，其他查找方式为精确包含",
    "    3.除help和all参数外，其他参数可任意组合使用,例如find -n 张三 -sex 女 -age 18"};

//lr显示的文字
char *lrstr[5] = {
    "共计%d个学校",
    "共计%d个学院",
    "共计%d个专业",
    "共计%d个班级",
    "共计%d个学生"};

//目前已去除相关命令，仅用于测试
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

//显示学生信息
int cat(tree p)
{
    if (!p || p->depth != 5)
        return FALSE;

    //清空屏幕
    cls();

    //打印信息
    gotoxy(50, 5);
    printf("姓名：%s", p->str);

    gotoxy(50, 5 + 1);
    if (p->data && ~p->data->sex)
        printf("性别：%s", p->data->sex ? "男" : "女");
    else
        printf("性别：%s", "不详");

    gotoxy(50, 5 + 2);
    if (p->data && ~p->data->age)
        printf("年龄：%d", p->data->age);
    else
        printf("年龄：%s", "不详");

    gotoxy(50, 5 + 3);
    printf("学校：%s", p->parents->parents->parents->parents->str);

    gotoxy(50, 5 + 4);
    printf("学院：%s", p->parents->parents->parents->str);

    gotoxy(50, 5 + 5);
    printf("专业：%s", p->parents->parents->str);

    gotoxy(50, 5 + 6);
    printf("班级：%s", p->parents->str);

    gotoxy(50, 5 + 7);
    if (p->data && ~p->data->ID)
        printf("学号：%d", p->data->ID);
    else
        printf("学号：%s", "不详");

    return TRUE;
}

//显示子目录
int ls(tree p)
{
    if (!p)
        return FALSE;

    //当前目录是学生的话，显示学生信息
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

//更新界面
void update(tree root, tree p)
{
    system("cls");
    prtree(root);
    printerface(p);
    ls(p);
}

//查看帮助
void help()
{
    cls();

    for (int i = 0; i < 18; i++)
    {
        gotoxy(38, 2 + i);
        puts(cmdhelp[i]);
    }
}

//字符串分割
int strcut(char *str, char *token[], char *delim)
{
    token[0] = strtok(str, delim);
    int i = 0;
    while (token[i] != NULL)
        token[++i] = strtok(NULL, delim);

    return i - 1;
}

//查找路径
tree finddir(tree p, tree root, char *str)
{
    if (!p)
        return FALSE;

    //父目录
    if (!strcmp(str, ".."))
    {
        if (p->parents)
            return p->parents;
        return NULL;
    }

    //当前目录
    if (!strcmp(str, "."))
        return p;

    //从父目录开始的路径
    if (!strncmp(str, "../", 3))
    {
        if (!p->parents)
            return NULL;
        root = p->parents;
        str += 2;
    }
    else if (!strncmp(str, "./", 2)) //从当前目录开始的路径
    {
        root = p;
        str++;
    }

    //非路径，直接搜索子目录
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

//切换目录
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

//创建新目录
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

//递归统计
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

//统计
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

//删除目录
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

//重命名
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

//修改学生信息
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
                if (!strcmp(token[i + 1], "男"))
                    sex = M;
                else if (!strcmp(token[i + 1], "女"))
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

//移动学生
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

//递归搜索
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

//搜索
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
                if (!strcmp(token[i + 1], "男"))
                    sex = M;
                else if (!strcmp(token[i + 1], "女"))
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
        printf("共搜索到%d条记录", k);

        gotoxy(38, 3);
        printf("%-10s%-10s%-10s%-10s%-10s%s", "姓名", "学校", "学院", "专业", "班级", "学号");

        for (int i = 0; i < k; i++)
        {
            gotoxy(38, 4 + i);
            printf("%-10s%-10s%-10s%-10s%-10s", list[i]->str, list[i]->parents->parents->parents->parents->str, list[i]->parents->parents->parents->str, list[i]->parents->parents->str, list[i]->parents->str);
            if (list[i]->data && ~list[i]->data->ID)
                printf("%d", list[i]->data->ID);
            else
                printf("%s", "不详");
        }
        return TRUE;
    }
    return FALSE;
}

//撤销
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