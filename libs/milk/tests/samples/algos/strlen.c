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

int my_strlen(const char* s)
{
  int len = 0;
  while (s[len] != 0)
    ++len;
  return len;
}

int main()
{
  char* str = malloc(6);
  str[0] = 'H';
  str[1] = 'e';
  str[2] = 'l';
  str[3] = 'l';
  str[4] = 'o';
  str[5] = 0;

  print_i64(my_strlen(str));
  putchar('\n');
  return 0;
}
