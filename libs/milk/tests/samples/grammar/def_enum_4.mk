enum MyEnum: i64 {
  FOO;
  BAR = 5;
  ZER = 7;
};


fn foo() : void {
  let x : MyEnum = MyEnum::FOO;
  x = MyEnum::ZER;
}
