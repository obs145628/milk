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

    

    let _x: f32;
    let _y: f32;
};
