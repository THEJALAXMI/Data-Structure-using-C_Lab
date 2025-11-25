#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int value;
    struct rep *repptr;
    struct node *next;
} node;

typedef struct rep
{
    node *head;
    node *tail;
} rep;

typedef struct nodaddr
{
    int key;
    node *obj_node_ptr;
    struct nodaddr *next;
} nodaddr;

nodaddr *ndr = 0;

void makeset(int a)
{
    nodaddr *t = (nodaddr*)malloc(sizeof(nodaddr));
    rep *newset = (rep*)malloc(sizeof(rep));    // FIXED
    node *n = (node*)malloc(sizeof(node));

    n->value = a;
    n->repptr = newset;
    n->next = 0;

    newset->head = newset->tail = n;

    t->obj_node_ptr = n;
    t->key = a;

    t->next = ndr;   // FIXED
    ndr = t;         // FIXED
}

rep* find(int x)
{
    nodaddr *t = ndr;

    while (t != NULL && t->key != x)   // FIXED
        t = t->next;

    if (t == NULL)
        return NULL;

    return t->obj_node_ptr->repptr;
}

void unionset(int key1, int key2)
{
    rep *set1, *set2;
    node *t1;

    set1 = find(key1);
    set2 = find(key2);

    if (set1 == NULL || set2 == NULL)
    {
        printf("\n One or both elements not found.\n");
        return;
    }

    if (set1 == set2)
    {
        printf("\n %d and %d belong to same set\n", key1, key2);
    }
    else
    {
        t1 = set2->head;

        while (t1 != 0)
        {
            t1->repptr = set1;
            t1 = t1->next;
        }

        set1->tail->next = set2->head;
        set1->tail = set2->tail;

        free(set2);

        printf("\n Union of %d and %d completed.\n", key1, key2);   // ADDED
    }
}

void display(int a)
{
    rep *r;
    node *t;

    r = find(a);

    if (r == NULL)
    {
        printf("\n Element not found.\n");
        return;
    }

    t = r->head;
    printf("\n Set members containing %d:", a);

    while (t != 0)
    {
        printf(" %d", t->value);
        t = t->next;
    }
}

void main()
{
    int data, data1, data2, opt;

    do
    {
        printf("\n 1.Makeset");
        printf("\n 2.Findset");
        printf("\n 3.Unionset");
        printf("\n 4.Display");
        printf("\n 5.Exit");
        printf("\n Enter your option: ");
        scanf("%d", &opt);

        switch (opt)
        {
            case 1:
                printf("\n Enter the data: ");
                scanf("%d", &data);
                makeset(data);
                break;

            case 2:
                printf("\n Enter set value: ");
                scanf("%d", &data);
                if (find(data) != NULL)
                    printf("\n Reference of set containing %d is %p\n", data, find(data));
                else
                    printf("Element not found.\n");
                break;

            case 3:
                printf("\n First data: ");
                scanf("%d", &data1);
                printf("\n Second data: ");
                scanf("%d", &data2);
                unionset(data1, data2);
                break;

            case 4:
                printf("\n Enter the data: ");
                scanf("%d", &data);
                display(data);
                break;

            case 5:
                exit(0);
        }

    } while (1);
}

