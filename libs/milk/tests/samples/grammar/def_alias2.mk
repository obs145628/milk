
type my_int = i32;
type int_cref = &const my_int;
type int_mref = & my_int;

fn store(dst: int_mref, src: int_cref) : void
{
  dst = src;
}
