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

double decimal_part(double x) {
  int64_t rel = x;
  return x > 0 ? x - rel : rel - x;
}

void print_f64(double x) {
  print_i64(x);
  x = decimal_part(x);
  putchar('.');

  for (int i = 0; i < 5; ++i) {
    x *= 10;
    putchar('0' + (char)x);
    x = decimal_part(x);
  }
}

int main() {
  print_f64(0);
  putchar('\n');

  print_f64(4);
  putchar('\n');

  print_f64(-7);
  putchar('\n');

  print_f64(134.5689);
  putchar('\n');

  print_f64(-43.25);
  putchar('\n');

  print_f64(168.632478);
  putchar('\n');

  print_f64(1.6578 / 1000);
  putchar('\n');

  return 0;
}
