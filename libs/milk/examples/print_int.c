#include <stdint.h>
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

int main() {
  print_i64(0);
  putchar('\n');

  print_i64(4);
  putchar('\n');

  print_i64(-7);
  putchar('\n');

  print_i64(179);
  putchar('\n');

  print_i64(-8543);
  putchar('\n');

  print_i64(156946287391);
  putchar('\n');

  print_i64(-78439174275198);
  putchar('\n');

  return 0;
}
