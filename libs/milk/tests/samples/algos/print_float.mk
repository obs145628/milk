fn decimal_part(x: f64): f64 {
  let rel : i64 = x;
  return x > 0 ? x - rel : rel - x;
}

fn print_f64(x: f64): void {
  print_i64(x);
  x = decimal_part(x);
  putchar('.');

  let i = 0;
  while (i < 5) {
    x *= 10;
    putchar('0' + x);
    x = decimal_part(x);
    i += 1;
  }
}

fn main(): void {
  print_f64(0);
  putchar('\n');

  print_f64(4);
  putchar('\n');

  print_f64(-7);
  putchar('\n');

  print_f64(134.5689);
  putchar('\n');

  print_f64(-43.25);
  putchar('\n');

  print_f64(168.632478);
  putchar('\n');

  print_f64(1.6578 / 1000);
  putchar('\n');

  return 0;
}


