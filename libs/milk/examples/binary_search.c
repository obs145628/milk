#include <stdlib.h>
#include <stdio.h>

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

int binsearch(int* arr, int len, int x)
{
  int beg = 0;
  int end = len;

  while (beg < end)
  {
    int mid = (beg + end) / 2;
    if (x < arr[mid])
      end = mid;
    else if (x > arr[mid])
      beg = mid + 1;
    else
      return mid;
  }

  return -1;
}

int main() {
  int *arr = malloc(11 * sizeof(int));
  arr[0] = -13;
  arr[1] = -7;
  arr[2] = -2;
  arr[3] = 1;
  arr[4] = 1;
  arr[5] = 3;
  arr[6] = 7;
  arr[7] = 45;
  arr[8] = 56;
  arr[9] = 78;
  arr[10] = 98;

  for (int i = 0; i < 11; ++i)
  {
    print_i64(i);
    putchar(' ');
    print_i64(binsearch(arr, 11, arr[i]));
    putchar('\n');
  }

  print_i64(binsearch(arr, 11, -15));
  putchar('\n');
  print_i64(binsearch(arr, 11, 2));
  putchar('\n');
  print_i64(binsearch(arr, 11, 99));
  putchar('\n');
  
  return 0;
}
