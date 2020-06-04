#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct node
{
    char *inf;
    struct node *children[10];
    int amount_children;
    int column;
    int line;
};

struct node* add_node(char *str, struct node *p);
void treeprint(struct node *p, int level);
void treefree(struct node *p);
void print_tree_in_file(struct node *p, int level, FILE *f);
#endif // TREE_H_INCLUDED
