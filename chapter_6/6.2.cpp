class Point
{
    public:
        Point(): xval(0), yval(0) { }
        Point(int x = 0, int y = 0): xval(x), yval(y) { }
        int x() const { return xval; }
        int y() const { return yval; }
        Point& x(int xv) { xval = xv; return *this; }
        Point& y(int yv) { yval = yv; return *this; }

    private:
        int xval, yval;
};
