
struct Pt {
  let x: i32;
  let y: i32;
};

struct Vec  {
  const p1: Pt;
  const p2: Pt;
  let in_check: bool;
};


fn foo() : void {
  Vec(.p1: Pt(.x:5, .y:7), .p2: Pt(.x:6, .y:3), .in_check: false);
}
