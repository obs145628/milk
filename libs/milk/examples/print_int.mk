fn print_i64_rec(x: i64): void {
  if (x == 0)
    return;

  print_i64_rec(x / 10);
  putchar('0' + x % 10);
}

fn print_i64(x: i64): void {
  if (x < 0) {
    putchar('-');
    print_i64(-x);
  }

  else if (x == 0)
    putchar('0');

  else
    print_i64_rec(x);
}

fn main(): void {
  print_i64(0);
  putchar('\n');

  print_i64(4);
  putchar('\n');

  print_i64(-7);
  putchar('\n');

  print_i64(179);
  putchar('\n');

  print_i64(-8543);
  putchar('\n');

  print_i64(156946287391);
  putchar('\n');

  print_i64(-78439174275198);
  putchar('\n');

  return 0;
}
