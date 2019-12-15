#include <stdlib.h>
#include <stdio.h>

void print_str(const char* str)
{
  while (*str != 0)
  {
    putchar(*str);
    str += 1;
  }
}

int my_strlen(const char* s)
{
  int len = 0;
  while (s[len] != 0)
    ++len;
  return len;
}

char* concat_str(const char* s1, const char* s2)
{
  int len1 = my_strlen(s1);
  int len2 = my_strlen(s2);
  char* res = malloc(len1 + len2 + 1);
  for (int i = 0; i < len1; ++i)
    res[i] = s1[i];
  for (int i = 0; i < len2; ++i)
    res[len1 + i] = s2[i];
  res[len1 + len2] = 0;
  return res;
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

  char* s2 = malloc(2);
  s2[0] = ' ';
  s2[1] = 0;

  char* s3 = malloc(6);
  s3[0] = 'W';
  s3[1] = 'o';
  s3[2] = 'r';
  s3[3] = 'l';
  s3[4] = 'd';
  s3[5] = 0;

  char* s = concat_str(s1, concat_str(s2, s3));
  print_str(s);
  putchar('\n');
  
  return 0;
}
