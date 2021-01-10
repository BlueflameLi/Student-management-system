//the coding is UTF-8

#include "tree.h"

//创建节点
tree createnode()
{
    tree p = (node *)malloc(sizeof(node));
    p->data = NULL;
    p->str = (char *)malloc(100 * sizeof(char));
    p->firstchild = p->nextsib = p->parents = NULL;
    p->depth = -1;
    return p;
}

//p添加一个儿子
int addnode(tree p, char *name, student *data)
{
    if (p)
    {
        if (p->depth == 5)
            return FALSE;
        if (!p->firstchild)
        {
            p->firstchild = createnode();
            strcpy(p->firstchild->str, name);
            p->firstchild->data = data;
            p->firstchild->parents = p;
            p->firstchild->depth = p->depth + 1;
        }
        else
        {
            tree q = p->firstchild;
            while (q->nextsib)
                q = q->nextsib;
            q->nextsib = createnode();
            strcpy(q->nextsib->str, name);
            q->nextsib->data = data;
            q->nextsib->parents = p;
            q->nextsib->depth = p->depth + 1;
        }
        return TRUE;
    }
    return FALSE;
}

//p的儿子里寻找name
tree find(tree p, char *name)
{
    if (!p)
        return NULL;
    if (p->firstchild)
    {
        if (!strcmp(p->firstchild->str, name))
            return p->firstchild;
        p = p->firstchild;
        while (p->nextsib)
        {

            if (!strcmp(p->nextsib->str, name))
                return p->nextsib;
            p = p->nextsib;
        }
    }
    return NULL;
}