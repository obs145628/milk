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

int64_t fibo_rec(int64_t x) {
  return x <= 1 ? x : fibo_rec(x - 2) + fibo_rec(x - 1);
}

int64_t fibo_iter(int64_t x) {
  if (x <= 1)
    return x;

  int64_t a = 0;
  int64_t b = 1;
  for (int64_t i = 1; i < x; ++i) {
    int64_t tmp = b;
    b += a;
    a = tmp;
  }

  return b;
}

int main() {
  for (int i = 0; i < 10; ++i) {
    print_i64(i);
    putchar('|');
    print_i64(fibo_rec(i));
    putchar('|');
    print_i64(fibo_iter(i));
    putchar('\n');
  }

  return 0;
}
