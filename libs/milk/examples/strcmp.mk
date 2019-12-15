
fn my_strcmp(s1: &const[] char, s2: &const[] char): i32
{
  let i = 0;
  while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
    i += 1;
  return s1[i] - s2[i];
}

fn main() : i32 {
  const s1 = v0h_infinite_array_ref(6, char(0));
  s1[0] = 'H';
  s1[1] = 'e';
  s1[2] = 'l';
  s1[3] = 'l';
  s1[4] = 'o';
  s1[5] = 0;

  const s2 = v0h_infinite_array_ref(6, char(0));
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
