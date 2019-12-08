

fn insertion_sort(arr: &[] int, len: usize): void {
  if (len <= 2)
    return;

  let i: usize = 1;
  while (i < len) {

    let val = arr[i];
    let j = i;
    while (j > 0 && arr[j - 1] > val) {
      arr[j] = arr[j - 1];
      j -= 1;
    }
    arr[j] = val;
    i += 1;
  }
}

fn main() : i32 {
  const arr = v0h_infinite_array_ref(11, i32(0));
  arr[0] = 13;
  arr[1] = -4;
  arr[2] = 7;
  arr[3] = 12;
  arr[4] = -6;
  arr[5] = 3;
  arr[6] = 7;
  arr[7] = 45;
  arr[8] = -4;
  arr[9] = 2;
  arr[10] = -1;

  print_arr(arr, 11);
  insertion_sort(arr, 11);
  print_arr(arr, 11);

  return 0;
}
