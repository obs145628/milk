struct S {
  let x: i32;
};


fn foo() : void {
  let s = S(.x: 8);
  s.x;
}
