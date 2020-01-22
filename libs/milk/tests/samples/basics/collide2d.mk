struct Vec2f
{

  fn __copy() const : Vec2f = default;

  fn static new(x: f32, y: f32) : Vec2f {
    return Vec2f (.x: x, .y: y);
  }

  let x: f32;
  let y: f32;
};

struct Circle
{

  fn __copy() const : Circle = default;

  fn static new(c: Vec2f, r: f32) : Circle {
    return Circle (.c: c, .r: r);
  }

  let c: Vec2f;
  let r: f32;

};

struct Rect
{

  fn __copy() const : Rect = default;

  fn static new(lt: Vec2f, rd: Vec2f) : Rect {
    return Rect (.lt: lt, .rt: rt);
  }

  let lt: Vec2f;
  let rd: Vec2f;
};

fn clamp(val: f32, min: f32, max: f32) : f32 {
  return val < min ? min : (val > max ? max : val);
}

fn check_cc(c1: &const Circle, c2: &const Circle) : bool {
  let dx = c2.x - c1.x;
  let dy = c2.y - c1.y;
  let dist = sqrt(dx*dx + dy*dy);
  return dist < c1.r + c2.r;
}

fn check_rr(r1: &const Rect, r2: &const Rect) : bool {
  return r1.lt.x < r2.rd.x && r1.rd.x > r2.lt.x
  && r1.lt.y < r2.rd.y && r1.rd.y > r2.lt.y;
}

fn check_cr(c: &const Circle, r: &const Rect) : bool {
  let clx = clamp(c.x, r.lt.x, r.rd.x);
  let cly = clamp(c.y, r.lt.y, r.rd.y);

  let dx = c.x - clx;
  let dy = c.y - cly;
  let dist2 = dx*dx + dy*dy;
  return dist2 < c.r * c.r;
}