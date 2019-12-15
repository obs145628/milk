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

int my_strcmp(const char* s1, const char* s2)
{
  int i = 0;
  while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
    i += 1;
  return s1[i] - s2[i];
}

int main()
{
  char* s1 = malloc(6);
  s1[0] = 'H';
  s1[1] = 'e';
  s1[2] = 'l';
  s1[3] = 'l';
  s1[4] = 'o';
  s1[5] = 0;

  char* s2 = malloc(6);
  s2[0] = 'W';
  s2[1] = 'o';
  s2[2] = 'r';
  s2[3] = 'l';
  s2[4] = 'd';
  s2[5] = 0;

  print_i64(my_strcmp(s1, s1));
  putchar('\n');
  print_i64(my_strcmp(s2, s2));
  putchar('\n');
  print_i64(my_strcmp(s1, s2));
  putchar('\n');
  print_i64(my_strcmp(s2, s1));
  putchar('\n');
  return 0;
}
