fn print_arr(arr: &[] int, len: usize): void {
  let i: usize = 0;
  while (i < len) {
    print_i64(arr[i]);
    if (i + 1 < len)
      putchar(';');
    i += 1;
  }
  putchar('\n');
}

fn swap(x: &int, y: &int) : void {
  let tmp : int = x;
  x = y;
  y = tmp;
}

fn bubble_sortr(arr: &[] int, len: usize): void {
  while (true) {
    let sorted = true;
    let i: usize = 0;
    while (i < len - 1) {
      if (arr[i] > arr[i + 1]) {
        swap(arr[i], arr[i + 1]);
        sorted = false;
      }
      i += 1;
    }

    if (sorted)
      break;
    --len;
  }
}

fn main() : i32 {
  const arr = v0h_infinite_array_ref(11, i32(0));
  arr[0] = 13;
  arr[1] = -4;
  arr[2] = 7;
  arr[3] = 12;
  arr[4] = -6;
  arr[6] = 7;
  arr[7] = 45;
  arr[8] = -4;
  arr[9] = 2;
  arr[10] = -1;

  print_arr(arr, 11);
  bubble_sort(arr, 11);
  print_arr(arr, 11);

  return 0;
}
