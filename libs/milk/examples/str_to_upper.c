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

char char_to_upper(char c)
{
  if (c >= 'a' && c <= 'z')
    return c + ('a' - 'A');
  else
    return c;
}

int str_to_upper(char* s)
{
  for (int i = 0; s[i] != 0; ++i)
    s[i] = char_to_upper(s[i]);
}

int main()
{
  char* str = malloc(8);
  str[0] = 'H';
  str[1] = 'e';
  str[2] = 'l';
  str[3] = 'l';
  str[4] = 'o';
  str[5] = ' ';
  str[6] = '!';
  str[7] = 0;

  str_to_upper(str);
  print_str(str);
  putchar('\n');
  return 0;
}
