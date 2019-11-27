#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;

void print_str(char* s)
{
    printf("%s", s);
}

void print_int(int x)
{
    printf("%d", (int) x);
}

void assert_fn(char* file, int line, char* mes, 
    bool res)
{
    if (!res)
    {
        print_str("assert_failed: ");
        print_str(file);
        print_str(":");
        print_int(line);
        print_str(": '");
        print_str(mes);
        print_str("'\n");
        exit(1);
    }
}

#define ASSERT(X) (assert_fn(__FILE__, __LINE__, #X, X))


typedef char* data_t;

int data_cmp(data_t a, data_t b)
{
    size_t i;

    i = 0;
    while (*(a + i) && *(b + i) && *(a + i) == *(b + i))
        i = i + 1;
    
    return (int) *(a + i) - (int) *(b + i);
}

typedef struct _BST BST;

struct _BST
{
    BST* parent;
    BST* left;
    BST* right;
    data_t data;
};

typedef struct
{
    BST* root;
    size_t size;
} Set;

typedef struct 
{
    int last_act;
    BST* node;
} SetIt;

void bst_free(BST* t)
{
    if ((*t).left != 0)
        bst_free((*t).left);
    if ((*t).right != 0)
        bst_free((*t).right);
    free(t);
}

BST* bst_new(data_t data, BST* parent)
{
    BST* res;

    res = malloc(sizeof(BST));
    (*res).parent = parent;
    (*res).left = 0;
    (*res).right = 0;
    (*res).data = data;
    return res;
}

BST* bst_min(BST* t)
{
    while ((*t).left != 0)
        t = (*t).left;
    return t;
}

BST* bst_max(BST* t)
{
    while ((*t).right != 0)
        t = (*t).right;
    return t;
}

BST* bst_find(BST* t, data_t data)
{
    int cmp;

    cmp = data_cmp(data, (*t).data);

    if (cmp < 0)
        return (*t).left != 0 ? bst_find((*t).left, data) : 0;
    else if (cmp > 0)
        return (*t).right != 0 ? bst_find((*t).right, data) : 0;
    else
        return t;
}

bool bst_insert(BST* t, data_t data)
{
    int cmp;

    cmp = data_cmp(data, (*t).data);

    if (cmp < 0)
    {
        if ((*t).left != 0)
            return bst_insert((*t).left, data);
        
        (*t).left = bst_new(data, t);
        return 1;
    }

    else if (cmp > 0)
    {
        if ((*t).right != 0)
            return bst_insert((*t).right, data);
        
        (*t).right = bst_new(data, t);
        return 1;
    }

    else
        return 0;
}

bool bst_remove(BST** root, BST* node, data_t data)
{
    BST** node_ptr;
    BST* p;

    node = (BST*) bst_find(node, data);
    if (node == 0)
        return 0;

    node_ptr = root;
    p = (*node).parent;
    if (p != 0)
    {
        if ((*p).left == node)
            node_ptr = &((*p).left);
        else
            node_ptr = &((*p).right);
    }

    //replace current node with right child
    if ((*node).left == 0)
    {
        *node_ptr = (*node).right;
        if (*node_ptr != 0)
            (*((*node).right)).parent = (*node).parent;
        free(node);
        return 1;
    }

    //replace current node with left child
    else if ((*node).right == 0)
    {
        *node_ptr = (*node).left;
        if (*node_ptr != 0)
            (*((*node).left)).parent = (*node).parent;
        free(node);
        return 1;
    }

    //replace node value with the min value of right child
    // (could be max value of left child)
    // then remove the replaced value
    else
    {
        (*node).data = (*bst_min((*node).right)).data;
        return bst_remove(root, (*node).right, (*node).data);
    }
        
}


//0: go down
//1: go up from left
//2: go up from right
void set_it_next(SetIt* it)
{
    BST* node;
    BST* next;
    int last_act;
    bool can_right;
    
    while (1)
    {
        last_act = (*it).last_act;
        node = (*it).node;
        if (node == 0)
            break;
        
        can_right = last_act <= 1 && (*node).right != 0;

        if (can_right)
        {
            (*it).node = bst_min((*node).right);
            (*it).last_act = 0;
            return;
        }

        else
        {
            next = (*node).parent;
            (*it).node = next;
            if (!next)
                continue;
            if ((*next).left == node)
            {
                (*it).last_act = 1;
                break;
            }
            else
                (*it).last_act = 2;
        }

    }
} 
    
data_t* set_it_get(SetIt* it)
{
    ASSERT((*it).node != 0);
    return &((*(*it).node).data);
}

bool set_it_eq(SetIt* a, SetIt* b)
{
    return (*a).node == (*b).node;
}


void set_init(Set* s)
{
    (*s).root = 0;
    (*s).size = 0;
}

void set_free(Set *s)
{
    if ((*s).root)
        bst_free((*s).root);
}

void set_clear(Set* s)
{
    set_free(s);
    set_init(s);
}

size_t set_size(Set* s)
{
    return (*s).size;
}

bool set_empty(Set* s)
{
    return (*s).size == 0;
}

bool set_contains(Set* s, data_t data)
{
    if ((*s).root == 0)
        return 0;
    return bst_find((*s).root, data) != 0;
}

data_t* set_get(Set* s, data_t data)
{
    BST* node;

    if ((*s).root == 0)
        return 0;
    
    node = bst_find((*s).root, data);
    if (node == 0)
        return 0;
    else
        return &((*node).data);   
}

bool set_insert(Set* s, data_t data)
{
    bool res;

    if ((*s).root == 0)
    {
        (*s).root = bst_new(data, 0);
        (*s).size = 1;
        return 1;
    }

    res = bst_insert((*s).root, data);
    if (res)
        (*s).size = (*s).size + 1;
    return res;
}

bool set_remove(Set* s, data_t data)
{
    bool res;

    if ((*s).root == 0)
        return 0;
    
    res = bst_remove(&((*s).root), (*s).root, data);
    if (res)
        (*s).size = (*s).size - 1;
    return res;
}

data_t set_min(Set* s)
{
    ASSERT((*s).root != 0);
    return (*bst_min((*s).root)).data;
}

data_t set_max(Set* s)
{
    ASSERT((*s).root != 0);
    return (*bst_max((*s).root)).data;
}

SetIt set_begin(Set* s)
{
    SetIt res;

    res.last_act = 0;
    if ((*s).root != 0)
        res.node =  (BST*) bst_min((*s).root);
    else
        res.node = 0;
    
    return res;
}

SetIt set_end(Set* s)
{
    SetIt res;

    res.node = 0;
    return res;
}


void set_print(Set* s)
{
    SetIt it;
    SetIt end;
    data_t* data;

    it = set_begin(s);
    end = set_end(s);
    print_str("{");

    while (!set_it_eq(&it, &end))
    {
        data = set_it_get(&it);
        print_str(*data);

        set_it_next(&it);
        if (!set_it_eq(&it, &end))
            print_str(", ");
    }

    print_str("}\n");
}






void test_basics()
{
    Set s;

    set_init(&s);
    ASSERT(set_empty(&s));
    ASSERT(set_size(&s) == 0);

    ASSERT(set_insert(&s, "tkt"));
    set_print(&s);
    ASSERT(!set_empty(&s));
    ASSERT(set_size(&s) == 1);

    set_clear(&s);
    set_print(&s);
    ASSERT(set_empty(&s));
    ASSERT(set_size(&s) == 0);

    set_free(&s);
}

void test_insert()
{
    Set s;
    
    set_init(&s);

    ASSERT(set_insert(&s, "c"));
    ASSERT(set_size(&s) == 1);
    set_print(&s);
    ASSERT(!set_insert(&s, "c"));

    ASSERT(set_insert(&s, "rust"));
    ASSERT(set_size(&s) == 2);
    set_print(&s);

    ASSERT(set_insert(&s, "c++"));
    ASSERT(set_size(&s) == 3);
    set_print(&s);

    ASSERT(set_insert(&s, "java"));
    ASSERT(set_size(&s) == 4);
    set_print(&s);

    ASSERT(set_insert(&s, "d"));
    ASSERT(set_size(&s) == 5);
    set_print(&s);

    ASSERT(set_insert(&s, "python"));
    ASSERT(set_size(&s) == 6);
    set_print(&s);

    ASSERT(set_insert(&s, "javascript"));
    ASSERT(set_size(&s) == 7);
    set_print(&s);

    ASSERT(set_insert(&s, "lua"));
    ASSERT(set_size(&s) == 8);
    set_print(&s);

    ASSERT(set_insert(&s, "ocaml"));
    ASSERT(set_size(&s) == 9);
    set_print(&s);

    ASSERT(set_insert(&s, "brainfuck"));
    ASSERT(set_size(&s) == 10);
    set_print(&s);

    ASSERT(set_insert(&s, "c#"));
    ASSERT(set_size(&s) == 11);
    set_print(&s);

    ASSERT(set_insert(&s, "objective-c"));
    ASSERT(set_size(&s) == 12);
    set_print(&s);

    ASSERT(set_insert(&s, "basic"));
    ASSERT(set_size(&s) == 13);
    set_print(&s);

    ASSERT(set_insert(&s, "go"));
    ASSERT(set_size(&s) == 14);
    set_print(&s);

    ASSERT(set_insert(&s, "asm"));
    ASSERT(set_size(&s) == 15);
    set_print(&s);

    ASSERT(set_contains(&s, "c"));
    ASSERT(set_contains(&s, "rust"));
    ASSERT(set_contains(&s, "c++"));
    ASSERT(set_contains(&s, "java"));
    ASSERT(set_contains(&s, "d"));
    ASSERT(set_contains(&s, "python"));
    ASSERT(set_contains(&s, "javascript"));
    ASSERT(set_contains(&s, "lua"));
    ASSERT(set_contains(&s, "ocaml"));
    ASSERT(set_contains(&s, "brainfuck"));
    ASSERT(set_contains(&s, "c#"));
    ASSERT(set_contains(&s, "objective-c"));
    ASSERT(set_contains(&s, "basic"));
    ASSERT(set_contains(&s, "go"));
    ASSERT(set_contains(&s, "asm"));

    ASSERT(!set_insert(&s, "c"));
    ASSERT(!set_insert(&s, "rust"));
    ASSERT(!set_insert(&s, "c++"));
    ASSERT(!set_insert(&s, "java"));
    ASSERT(!set_insert(&s, "d"));
    ASSERT(!set_insert(&s, "python"));
    ASSERT(!set_insert(&s, "javascript"));
    ASSERT(!set_insert(&s, "lua"));
    ASSERT(!set_insert(&s, "ocaml"));
    ASSERT(!set_insert(&s, "brainfuck"));
    ASSERT(!set_insert(&s, "c#"));
    ASSERT(!set_insert(&s, "objective-c"));
    ASSERT(!set_insert(&s, "basic"));
    ASSERT(!set_insert(&s, "go"));
    ASSERT(!set_insert(&s, "asm"));

    set_clear(&s);
    set_print(&s);
    set_free(&s);
}

void test_remove()
{
    Set s;

    set_init(&s);

    ASSERT(set_insert(&s, "tf"));
    ASSERT(set_insert(&s, "numpy"));
    ASSERT(set_insert(&s, "scipy"));
    ASSERT(set_insert(&s, "torch"));
    ASSERT(set_insert(&s, "django"));
    ASSERT(set_insert(&s, "flask"));
    ASSERT(set_insert(&s, "pandas"));
    ASSERT(set_insert(&s, "sklearn"));
    ASSERT(set_insert(&s, "matplotlib"));
    ASSERT(set_insert(&s, "pickle"));
    set_print(&s);
    ASSERT(set_size(&s) == 10);

    ASSERT(set_remove(&s, "tf"));
    set_print(&s);
    ASSERT(set_remove(&s, "numpy"));
    set_print(&s);
    ASSERT(set_remove(&s, "scipy"));
    set_print(&s);
    ASSERT(set_remove(&s, "torch"));
    set_print(&s);
    ASSERT(set_remove(&s, "django"));
    set_print(&s);
    ASSERT(set_remove(&s, "flask"));
    set_print(&s);
    ASSERT(set_remove(&s, "pandas"));
    set_print(&s);
    ASSERT(set_remove(&s, "sklearn"));
    set_print(&s);
    ASSERT(set_remove(&s, "matplotlib"));
    set_print(&s);
    ASSERT(set_remove(&s, "pickle"));
    set_print(&s);
    ASSERT(set_size(&s) == 0);
    set_free(&s);
}

void test_print()
{
    Set s;

    set_init(&s);
    set_print(&s);
    ASSERT(set_insert(&s, "56"));
    ASSERT(set_insert(&s, "45"));
    ASSERT(set_insert(&s, "28"));
    ASSERT(set_insert(&s, "12"));
    set_print(&s);

    ASSERT(set_remove(&s, "45"));
    ASSERT(set_insert(&s, "17"));
    ASSERT(set_insert(&s, "49"));
    set_print(&s);

    ASSERT(set_remove(&s, "56"));
    ASSERT(set_remove(&s, "28"));
    ASSERT(set_insert(&s, "40"));
    set_print(&s);

    set_free(&s);
}

int main()
{
    test_basics();
    test_insert();
    test_remove();
    test_print();

    return 0;
}