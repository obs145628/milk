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

void swap(int *x, int *y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

size_t choose_pivot(int *arr, size_t beg, size_t end) {
  size_t i = beg;
  size_t j = beg + (end - beg) / 2;
  size_t k = end - 1;

  if (arr[i] > arr[j]) {
    if (arr[j] > arr[k])
      return j;
    else if (arr[i] > arr[k])
      return k;
    else
      return i;
  } else {
    if (arr[i] > arr[k])
      return i;
    else if (arr[j] > arr[k])
      return k;
    else
      return j;
  }
}

size_t partition(int *arr, size_t beg, size_t end, size_t p) {
  int pval = arr[p];
  swap(arr + p, arr + end - 1);

  size_t low = beg;
  size_t high = end - 1;

  while (low < high) {
    if (arr[low] <= pval)
      low += 1;
    else {
      high -= 1;
      swap(arr + high, arr + low);
    }
  }

  swap(arr + end - 1, arr + low);
  return low;
}

void quicksort(int *arr, size_t beg, size_t end) {
  size_t len = end - beg;
  if (len < 2)
    return;

  size_t p = choose_pivot(arr, beg, end);
  p = partition(arr, beg, end, p);
  quicksort(arr, 0, p);
  quicksort(arr, p + 1, end);
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
  quicksort(arr, 0, 11);
  print_arr(arr, 11);

  return 0;
}
