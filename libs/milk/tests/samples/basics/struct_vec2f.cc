class Vec2f
{
public:

  Vec2f(float x, float y)
    : _x(x), _y(y) {}

  static Vec2f zero() { return Vec2f(0, 0); }


  float get_x() const { return _x; }
  float get_y() const { return _y; }
  void set_x(float x) { _x = x; }
  void set_y(float y) { _y = y; }

  float norm_sq() const { return _x*_x + _y*_y; }

  void translate(float dx, float dy)
  {
    _x += dx;
    _y += dy;
  }

  Vec2f neg() const
  {
    return Vec2f(_x, _y);
  }

  

private:  
  float _x;
  float _y;
};


float dist_sq(const Vec2f& a, const Vec2f& b)
{
  float dx = a.get_x() - b.get_x();
  float dy = a.get_y() - b.get_y();
  return dx * dx + dy * dy;
}

float dot(const Vec2f& a, const Vec2f& b)
{
  return a.get_x() * b.get_x() + a.get_y() * b.get_y();
}

Vec2f add(const Vec2f& a, const Vec2f& b)
{
  return Vec2f(a.get_x() + b.get_x(), a.get_y() + b.get_y());
}


bool equals(const Vec2f& a, const Vec2f& b)
{
  return a.get_x() == b.get_x() && a.get_y() == b.get_y();
}

