#include "tree.h"

struct node* add_node(char *str, struct node *p)
{
    if (p == NULL)   // Если дерева нет, то формируем корень
    {
        p =(struct node*)malloc(sizeof(struct node)); // память под узел
        p->inf = malloc(strlen(str));   // поле данных
        strcpy(p->inf, str);
        p->amount_children=0;
        for (int i=0; i<10; i++)
            p->children[i] = NULL;
    }
    else
    {
        p->children[p->amount_children]=add_node(str,p->children[p->amount_children]);
        p->amount_children=p->amount_children+1;
        p=p->children[p->amount_children-1];
    }
    return p;
}

void treeprint(struct node *p, int level)
{
    if (p!=NULL)
    {
        puts(p->inf);
        for (int i=0; i<p->amount_children; i++)
        {
            for(int j = 0; j< level; j++)
                printf("*");
            treeprint(p->children[i], level+1);
        }
    }
}

void treefree(struct node *p)
{
    if (p!=NULL)
    {
        for (int i=0; i<p->amount_children; i++)
        {
            treefree(p->children[i]);
        }
        free(p);
    }
}

void print_tree_in_file(struct node *p, int level, FILE *f)
{
    if (p!=NULL)
    {
        fputs(p->inf, f);
        fprintf(f,"\n");
        for (int i=0; i<p->amount_children; i++)
        {
            for(int j = 0; j< level; j++)
                fprintf(f,"*");
            print_tree_in_file(p->children[i], level+1, f);
        }
    }
}
