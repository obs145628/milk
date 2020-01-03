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

void bubble_sort(int *arr, size_t len) {
  while (1) {
    int sorted = 1;
    for (int i = 0; i < len - 1; ++i) {
      if (arr[i] > arr[i + 1]) {
        swap(arr + i, arr + i + 1);
        sorted = 0;
      }
    }

    if (sorted)
      break;
    --len;
  }
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
  bubble_sort(arr, 11);
  print_arr(arr, 11);

  return 0;
}
