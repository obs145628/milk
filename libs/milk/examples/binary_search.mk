
fn binsearch(arr: &[] i32, len: i32, x: i32)
{
  let beg: i32 = 0;
  let end = len;

  while (beg < end)
  {
    let mid = (beg + end) / 2;
    if (x < arr[mid])
      end = mid;
    else if (x > arr[mid])
      beg = mid + 1;
    else
      return mid;
  }

  return -1;
}

fn main() : i32 {
  const arr = v0h_infinite_array_ref(11, i32(0));
  arr[0] = -13;
  arr[1] = -7;
  arr[2] = -2;
  arr[3] = 1;
  arr[4] = 1;
  arr[5] = 3;
  arr[6] = 7;
  arr[7] = 45;
  arr[8] = 56;
  arr[9] = 78;
  arr[10] = 98;

  let i: i32 = 0;
  while (i < 11)
  {
    print_i64(i);
    putchar(' ');
    print_i64(binsearch(arr, 11, arr[i]));
    putchar('\n');
    i += 1;
  }

  print_i64(binsearch(arr, 11, -15));
  putchar('\n');
  print_i64(binsearch(arr, 11, 2));
  putchar('\n');
  print_i64(binsearch(arr, 11, 99));
  putchar('\n');

  return 0;
}
