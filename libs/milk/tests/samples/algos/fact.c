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

int64_t fact_rec(int64_t x) { return x <= 1 ? 1 : x * fact_rec(x - 1); }

int64_t fact_iter(int64_t x) {
  int64_t res = 1;
  while (x >= 2) {
    res *= x;
    x -= 1;
  }

  return res;
}

int main() {
  for (int i = 0; i < 10; ++i) {
    print_i64(i);
    putchar('|');
    print_i64(fact_rec(i));
    putchar('|');
    print_i64(fact_iter(i));
    putchar('\n');
  }

  return 0;
}
