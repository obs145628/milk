fn fact_rec(x: u64): u64
{
  return x <= 1 ? 1 : x * fact(x - 1);
}

fn fact_iter(x: u64): u64
{
  let res: u64 = 1;
  while (x >= 2) {
    res *= x;
    x -= 1;
  }

  return res;
}

fn main() : i32 {
  let i : i32 = 0;
  while (i < 10) {
    print_i64(i);
    putchar('|');
    print_i64(fact_rec(i));
    putchar('|');
    print_i64(fact_iter(i));
    putchar('\n');
  }

  return 0;
}
