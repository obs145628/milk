#include <stdio.h>
#include <stdlib.h>

void print_i64_rec(int64_t x) {
  if (!x)
    return;

  print_i64_rec(x / 10);
  putchar('0' + x % 10);
}

void print_i64(int64_t x) {
  if (x < 0) {
    putchar('-');
    print_i64(-x);
  }

  else if (x == 0)
    putchar('0');

  else
    print_i64_rec(x);
}

void print_arr(int *arr, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    print_i64(arr[i]);
    if (i + 1 < len)
      putchar(';');
  }
  putchar('\n');
}

void merge(int *arr, size_t beg, size_t m, size_t end) {
  size_t len = end - beg;
  char *tmp = malloc(len * sizeof(int));

  size_t i1 = beg;
  size_t i2 = m;

  for (size_t i = 0; i < len; ++i) {
    if (i2 >= end || (i1 < m && arr[i1] < arr[i2]))
      tmp[i] = arr[i1++];
    else
      tmp[i] = arr[i2++];
  }

  for (size_t i = 0; i < len; ++i)
    arr[beg + i] = tmp[i];

  free(tmp);
}

void mergesort(int *arr, size_t beg, size_t end) {
  size_t len = end - beg;
  if (len < 2)
    return;

  size_t m = beg + (end - beg + 1) / 2;
  mergesort(arr, beg, m);
  mergesort(arr, m, end);
  merge(arr, beg, m, end);
}

int main() {
  int *arr = malloc(11 * sizeof(int));

  arr[0] = 13;
  arr[1] = -4;
  arr[2] = 7;
  arr[3] = 12;
  arr[4] = -6;
  arr[5] = 3;
  arr[6] = 7;
  arr[7] = 45;
  arr[8] = -4;
  arr[9] = 2;
  arr[10] = -1;

  print_arr(arr, 11);
  mergesort(arr, 0, 11);
  print_arr(arr, 11);

  return 0;
}
