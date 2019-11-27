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

typedef struct
{
    int* arr;
    size_t size;
    size_t cap;
} Vector;

void vector_init(Vector* v)
{
    (*v).size = 0;
    (*v).cap = 2;
    (*v).arr = malloc(v->cap * sizeof(int));
}

void vector_free(Vector* v)
{
    free((*v).arr);
}

int* vector_begin(Vector* v)
{
    return (*v).arr;
}

int* vector_end(Vector* v)
{
    return (*v).arr + (*v).size;
}

size_t vector_size(Vector* v)
{
    return (*v).size;
}

bool vector_empty(Vector* v)
{
    return (*v).size == 0;
}

void vector_reserve(Vector* v, size_t len)
{
    if ((*v).cap >= len)
        return;
    (*v).cap = len;
    int* new_data = malloc(v->cap * sizeof(int));
    memcpy(new_data, (*v).arr, (*v).size * sizeof(int));

    free((*v).arr);
    (*v).arr = new_data;
}

void vector_resize(Vector* v, size_t len)
{
    size_t new_cap = (*v).cap;
    while (new_cap < len)
        new_cap *= 2;
    if (new_cap != (*v).cap)
        vector_reserve(v, new_cap);
    (*v).size = len;
}

void vector_clear(Vector* v)
{
    vector_resize(v, 0);
} 

int vector_get(Vector* v, size_t i)
{
    ASSERT(i < (*v).size);
    return *((*v).arr + i);
}

void vector_set(Vector* v, size_t i, int x)
{
    ASSERT(i < (*v).size);
    *((*v).arr + i) = x;
}

void vector_push_back(Vector* v, int x)
{
    vector_resize(v, (*v).size + 1);
    vector_set(v, (*v).size - 1, x);
}

void vector_insert(Vector* v, size_t i, int x)
{
    ASSERT(i <= (*v).size);
    memmove((*v).arr + i + 1, (*v).arr + i, ((*v).size - i) * sizeof(int));
    (*v).size = (*v).size + 1;
    vector_set(v, i, x);
}

void vector_remove(Vector* v, size_t i, size_t nb)
{
    if (nb == 0)
        return;
    
    ASSERT(i < (*v).size);
    ASSERT(i + nb <= (*v).size);

    size_t nmove = (*v).size - i - nb;
    memmove((*v).arr + i, (*v).arr + i + nb, nmove * sizeof(int));
    (*v).size = (*v).size - nb;
}

void vector_assign(Vector* dst, Vector* src)
{
    vector_resize(dst, (*src).size);
    memcpy((*dst).arr, (*src).arr, (*src).size * sizeof(int));
}

void vector_print(Vector* v)
{
    print_str("{");
    size_t i = 0;
    while (i < (*v).size)
    {
        print_int(vector_get(v, i));
        if (i + 1 < vector_size(v))
            print_str(", ");
        i = i + 1;
    }
    print_str("}\n");
}




void test_basics()
{
    Vector v;
    vector_init(&v);
    ASSERT(vector_empty(&v));
    ASSERT(vector_size(&v) == 0);
    ASSERT(vector_begin(&v) == v.arr);
    ASSERT(vector_end(&v) == v.arr);

    int i = 0;
    while (i < 10)
    {
        vector_push_back(&v, i);
        i = i + 1;
    }

    ASSERT(!vector_empty(&v));
    ASSERT(vector_size(&v) == 10);
    ASSERT(vector_begin(&v) == v.arr);
    ASSERT(vector_end(&v) == v.arr + 10);

    vector_clear(&v);
    ASSERT(vector_empty(&v));
    ASSERT(vector_size(&v) == 0);
    ASSERT(vector_begin(&v) == v.arr);
    ASSERT(vector_end(&v) == v.arr);

    vector_free(&v);
}

void test_resize_get_set()
{
    Vector v;
    vector_init(&v);
    ASSERT(vector_size(&v) == 0);
    vector_resize(&v, 8);
    ASSERT(vector_size(&v) == 8);

    int i = 0;
    while (i < 8)
    {
        vector_set(&v, i, i*i*i);
        i = i + 1;
    }

    vector_print(&v);
    i = 0;
    while (i < 8)
    {
        ASSERT(vector_get(&v, i) == i*i*i);
        i = i + 1;
    }

    vector_resize(&v, 3);
    vector_print(&v);
    ASSERT(vector_size(&v) == 3);

    i = 0;
    while (i < 3)
    {
        ASSERT(vector_get(&v, i) == i*i*i);
        i = i + 1;
    }

    vector_resize(&v, 0);
    ASSERT(vector_size(&v) == 0);

    vector_free(&v);
}

void test_insert()
{
    Vector v;
    vector_init(&v);
    vector_push_back(&v, 10);
    vector_push_back(&v, 56);
    vector_push_back(&v, 45);
    vector_print(&v);
    ASSERT(vector_get(&v, 0) == 10);
    ASSERT(vector_get(&v, 1) == 56);
    ASSERT(vector_get(&v, 2) == 45);

    vector_insert(&v, 0, 7);
    vector_print(&v);
    ASSERT(vector_get(&v, 0) == 7);
    ASSERT(vector_get(&v, 1) == 10);
    ASSERT(vector_get(&v, 2) == 56);
    ASSERT(vector_get(&v, 3) == 45);
    
    vector_insert(&v, 2, 18);
    vector_print(&v);
    ASSERT(vector_get(&v, 0) == 7);
    ASSERT(vector_get(&v, 1) == 10);
    ASSERT(vector_get(&v, 2) == 18);
    ASSERT(vector_get(&v, 3) == 56);
    ASSERT(vector_get(&v, 4) == 45);

    vector_insert(&v, 5, 59);
    vector_print(&v);
    ASSERT(vector_get(&v, 0) == 7);
    ASSERT(vector_get(&v, 1) == 10);
    ASSERT(vector_get(&v, 2) == 18);
    ASSERT(vector_get(&v, 3) == 56);
    ASSERT(vector_get(&v, 4) == 45);
    ASSERT(vector_get(&v, 5) == 59);
}

void test_remove()
{
    Vector v;
    vector_init(&v);

    vector_push_back(&v, 10);
    vector_push_back(&v, 56);
    vector_push_back(&v, 45);
    vector_push_back(&v, 12);
    vector_push_back(&v, 17);
    vector_print(&v);

    vector_remove(&v, 1, 2);
    vector_print(&v);
    ASSERT(vector_size(&v) == 3);
    ASSERT(vector_get(&v, 0) == 10);
    ASSERT(vector_get(&v, 1) == 12);
    ASSERT(vector_get(&v, 2) == 17);

    vector_remove(&v, 0, 1);
    vector_print(&v);
    ASSERT(vector_size(&v) == 2);
    ASSERT(vector_get(&v, 0) == 12);
    ASSERT(vector_get(&v, 1) == 17);

    vector_remove(&v, 1, 1);
    vector_print(&v);
    ASSERT(vector_size(&v) == 1);
    ASSERT(vector_get(&v, 0) == 12);
}

void test_print()
{
    Vector v;
    vector_init(&v);
    vector_push_back(&v, 4);
    vector_push_back(&v, 5);
    vector_push_back(&v, 2);
    vector_push_back(&v, 3);
    vector_print(&v);
    vector_free(&v);
}

int main()
{
    test_basics();
    test_resize_get_set();
    test_insert();
    test_remove();
    test_print();
}

