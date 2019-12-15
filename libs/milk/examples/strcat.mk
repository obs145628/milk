
fn concat_str(s1: &const[] char, s2: &const[] char) : &[] char
{
  let len1 = my_strlen(s1);
  let len2 = my_strlen(s2);
  const res = v0h_infinite_array_ref(len1 + len2 + 1, 0);

  let i = 0;
  while (i < len1) {
    res[i] = s1[i];
    i += 1;
  }

  i = 0;
  while (i < len2) {
    res[len1 + i] = s2[i];
    i += 1;
  }

  res[len1 + len2] = 0;
  return res;
}

fn main() : i32 {
  const s1 = v0h_infinite_array_ref(6, char(0));
  s1[0] = 'H';
  s1[1] = 'e';
  s1[2] = 'l';
  s1[3] = 'l';
  s1[4] = 'o';
  s1[5] = 0;

  const s2 = v0h_infinite_array_ref(2, char(0));
  s2[0] = ' ';
  s2[1] = 0;

  const s3 = v0h_infinite_array_ref(6, char(0));
  s3[0] = 'W';
  s3[1] = 'o';
  s3[2] = 'r';
  s3[3] = 'l';
  s3[4] = 'd';
  s3[5] = 0;

  const s = concat_str(s1, concat_str(s2, s3));
  print_str(s);
  putchar('\n');
  return 0;
}
