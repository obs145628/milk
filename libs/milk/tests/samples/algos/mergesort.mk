

fn merge(arr: &[] int, beg: usize, m: usize, end: usize): void {
  let len = end - beg;
  const tmp = v0h_infinite_array_ref(len, i32(0));

  let i1 = beg;
  let i2 = m;
  let i : usize = 0;

  while (i < len) {
    if (i2 >= end || (i1 < m && arr[i1] < arr[i2])) {
      tmp[i] = arr[i1];
      i1 += 1;
    }
    else {
      tmp[i] = arr[i2];
      i2 += 1;
    }
    i += 1;
  }

  i = 0;
  while (i < len) {
    arr[beg + i] = tmp[i];
    i += 1;
  }
}


fn mergesort(arr: &[] int, beg: usize, end: usize): void {
  let len = end - beg;
  if (len < 2)
    return;

  let m = beg + (end - beg + 1) / 2;
  mergesort(arr, beg, m);
  mergesort(arr, m, end);
  merge(arr, beg, m, end);
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
  mergesort(arr, 0, 11);
  print_arr(arr, 11);

  return 0;
}
