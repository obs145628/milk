
fn my_strlen(str: &[]const char) : i32
{
  let len : i32 = 0;
  while (str[len] != 0)
  {
    len += 1;
  }
  return len;
}

fn char_to_upper(c: char) : char
{
  if (c >= 'a' && c <= 'z')
    return c + ('a' - 'A');
  else
    return c;
}

fn str_to_upper(str: &[] char): void
{
  let i : i32 = 0;
  while (s[i] != 0) {
    s[i] = char_to_upper(s[i]);
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
  str[5] = ' ';
  str[6] = '!';
  str[7] = 0;

  str_to_upper(str);
  print_str(str);
  putchar('\n');
  return 0;
}

