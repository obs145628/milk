fn fibo_rec(x: i64): i64 {
  return x <= 1 ? x : fibo_rec(x - 2) + fibo_rec(x - 1);
}

fn fibo_iter(x: i64): i64 {
  if (x <= 1)
    return x;

  let a : i64 = 0;
  let b : i64 = 1;
  let i : i64 = 1;
  while (i < x) {
    let tmp = b;
    b += a;
    a = tmp;
    i += 1;
  }

  return b;
}

fn main() : i32 {
  let i : i32 = 0;
  while (i < 10) {
    print_i64(i);
    putchar('|');
    print_i64(fibo_rec(i));
    putchar('|');
    print_i64(fibo_iter(i));
    putchar('\n');
  }

  return 0;
}
