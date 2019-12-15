
fn my_strlen(str: &const[] char) : i32
{
  let len : i32 = 0;
  while (str[len] != 0)
  {
    len += 1;
  }
  return len;
}


fn main() : i32 {
  const str = v0h_infinite_array_ref(6, char(0));
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
