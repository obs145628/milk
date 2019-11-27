#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    struct Node* next;
};

struct List
{
    struct Node* root;
    int size;
};

void list_init(struct List* l)
{
    l->root = 0;
    l->size = 0;
}

void list_clear(struct List* l)
{
    struct Node* node = l->root;
    while (node)
    {
        struct Node* next = node->next;
        free(node);
        node = next;
    }

    l->root = 0;
    l->size = 0;
}

void list_push_back(struct List* l, int x)
{
    struct Node** last = &(l->root);
    while (*last)
        last = &((*last)->next);
    *last = malloc(sizeof(struct Node));
    (*last)->val = x;
    (*last)->next = 0;
    l->size += 1;
}

void list_push_front(struct List* l, int x)
{
    struct Node* head = malloc(sizeof(struct Node));
    head->val = x;
    head->next = l->root;

    l->root = head;
    l->size += 1;
}

void list_pop_back(struct List* l)
{
    if (!l->root)
        return;

    struct Node** prev = &(l->root);
    while ((*prev)->next)
        prev = &((*prev)->next);
    free(*prev);
    *prev = NULL;
    l->size -= 1;
}

void list_pop_front(struct List* l)
{
    if (!l->root)
        return;
    
    struct Node* head = l->root->next;
    free(l->root);
    l->root = head;
    l->size -= 1;
}

void list_print(struct List const* l)
{
    printf("{");
    struct Node* node = l->root;
    while (node) {
        printf("%d", node->val);
        if (node->next)
            printf(", ");
        node = node->next;
    }
    printf("}\n");
}

int main()
{

    struct List l;
    list_init(&l);
    list_print(&l);

    list_push_back(&l, 18);
    list_push_front(&l, 9);
    list_push_front(&l, 5);
    list_push_back(&l, 24);
    list_push_front(&l, 4);
    list_push_back(&l, 27);
    list_print(&l);

    list_pop_back(&l);
    list_pop_front(&l);
    list_print(&l);
    list_pop_front(&l);
    list_pop_front(&l);
    list_print(&l);
    list_pop_back(&l);
    list_pop_back(&l);
    
    list_print(&l);
    list_push_front(&l, 5);
    list_print(&l);
    list_pop_front(&l);
    list_print(&l);

    for (int i = 0; i < 10; ++i)
        list_push_front(&l, i*i);
    list_print(&l);

    list_clear(&l);
    list_print(&l);

    return 0;
}