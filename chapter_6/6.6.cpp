/**********************************************
    Programmer  :   EOF
    Date        :   2015.05.19
    File        :   6.6.cpp
    E-mail      :   jasonleaster@gmail.com

**********************************************/
#include <iostream>

using namespace std;

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

/*
   This class is used for store the @Point class and count @u
 */
class UPoint
{
    friend class Handle;
    Point p;
    int counter;

    UPoint(): counter(1) { }
    UPoint(int x, int y): p(x, y), counter(1)  { }
    UPoint(const Point& p0): p(p0), counter(1) { }
};

class Handle
{
    public:
        Handle();
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
        /*
            All we have done in @Handle is to maintain this data member :)
         */
        UPoint *up;
};

Handle::~Handle()
{
    if (--up->counter == 0)
    {
        delete up;
    }
}

/*
   Constructor function of @Handle
 */
Handle::Handle(): up(new UPoint) { }
Handle::Handle(int x, int y): up(new UPoint(x, y)) { }
Handle::Handle(const Point& p): up(new UPoint(p)) { }
Handle::Handle(const Handle& h): up(h.up) { ++up->counter; }

Handle&
Handle::operator = (const Handle& h)
{
    ++(h.up->counter);
    if(--(up->counter) == 0)
    {
        delete up;
    }

    up = h.up;
    return *this;
}

int Handle::x() const { return up->p.x(); }
int Handle::y() const { return up->p.y(); }

Handle& Handle::x(int x0)
{
    up->p.x(x0);
    return *this;
}

Handle& Handle::y(int y0)
{
    up->p.y(y0);
    return *this;
}

int main()
{
    Handle h(3, 4);
    Handle h2 = h;

    h2.x(5);

    int n = h.x();

    cout << "n = " << n << endl;
    return 0;
}
