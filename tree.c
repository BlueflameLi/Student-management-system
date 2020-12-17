#include "tree.h"

tree createnode()
{
    tree p = (node *)malloc(sizeof(node));
    p->data = NULL;
    p->str = NULL;
    p->firstchild = p->nextsib = p->parents = NULL;
}
int addnode(tree p, char *name, student *data)
{
    if (p)
    {
        if (!p->firstchild)
        {
            p->firstchild = createnode();
            p->firstchild->str = name;
            p->firstchild->data = data;
            p->firstchild->parents = p;
        }
        else
        {
            tree q = p->firstchild;
            while (q->nextsib)
                q = q->nextsib;
            q->nextsib = createnode();
            q->nextsib->str = name;
            q->nextsib->data = data;
            q->nextsib->parents = p;
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
        if (p->firstchild->str == name)
            return p->firstchild;
        p = p->firstchild;
        while (p->nextsib)
        {

            if (p->nextsib->str == name)
                return p->nextsib;
            p = p->nextsib;
        }
    }
    return NULL;
}