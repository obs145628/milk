enum MyEnum: i64 {
  FOO;
  BAR = 5;
  ZER = 7;
};


fn foo() : void {
  let x : MyEnum = MyEnum::FOO;
  let y = i32(x) + 1;
  x = MyEnum::ZER;
}
