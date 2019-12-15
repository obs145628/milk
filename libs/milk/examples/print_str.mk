fn print_str(str: &const[] char) : void
{
  let i : i32 = 0;
  while (str[i] != 0)
  {
    putchar(str[i]);
    i += 1;
  }
}


fn main() : i32 {
  const str = v0h_infinite_array_ref(6, char(0));
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
