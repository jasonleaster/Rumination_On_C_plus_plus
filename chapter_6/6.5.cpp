class Point
{
    public:
        Point(): xval(0), yval(0) { }
        Point(int x, int y): xval(x), yval(y) { }
        int x() const { return xval; }
        int y() const { return yval; }
        Point& x(int xv) { xval = xv; return *this; }
        Point& y(int yv) { yval = yv; return *this; }

    private:
        int xval, yval;
};

class Handle
{
    public:
        Handle(){};
        Handle(int, int);
        Handle(const Point&);
        Handle(const Handle&);
        Handle& operator=(const Handle&);
        ~Handle();

        int x() const;
        Handle& x(int);
        int y() const;
        Handle& y(int);

    private:
        // ...
};
