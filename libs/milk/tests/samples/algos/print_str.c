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

int main()
{
  char* str = malloc(6);
  str[0] = 'H';
  str[1] = 'e';
  str[2] = 'l';
  str[3] = 'l';
  str[4] = 'o';
  str[5] = 0;

  print_str(str);
  putchar('\n');
  
  return 0;
}
