struct Vec2f
{

    fn __copy() const : Vec2f = default;

    fn static new(x: f32, y: f32) : Vec2f {
        return Vec2f (
            ._x: x,
            ._y: y
        );
    }

    fn static zero(): Vec2f
    {
        return Vec2::new(0, 0);
    }

    fn get_x() const : f32 { return self._x; }
    fn get_y() const : f32 { return self._y; }

    fn set_x(x: f32): void { self._x = x; }
    fn set_y(y: f32): void { self._y = y; }

    fn norm_sq() const : f32 { return self._x*self._x + self._y*self._y; }

    fn translate(dx: f32, dy: f32) : void
    {
      self._x += dx;
      self._y += dy;
    }

    fn neg() const : Vec2f
    {
      return Vec2f::new(self._x, self._y);
    }

    let _x: f32;
    let _y: f32;
};

fn dist_sq(a: &const Vec2f, b: &const Vec2f): f32
{
  let dx = a.get_x() - b.get_x();
  let dy = a.get_y() - b.get_y();
  return dx * dx + dy * dy;
}

fn dot(a: &const Vec2f, b: &const Vec2f): f32
{
  return a.get_x() * b.get_x() + a.get_y() * b.get_y();
}

fn add(a: &const Vec2f, b: &const Vec2f): Vec2f
{
  return Vec2f::new(a.get_x() + b.get_x(), a.get_y() + b.get_y());
}


fn equals(a: &const Vec2f, b: &const Vec2f): bool
{
  return a.get_x() == b.get_x() && a.get_y() == b.get_y();
}
