/**********************************************
    Programmer  :   EOF
    Date        :   2015.05.19
    File        :   7.2.cpp
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
        // what we added
        Point *p;
        int *u;
};

Handle::~Handle()
{
    if (--*u == 0)
    {
        delete u;
        delete p;
    }
}

/*
   Constructor function of @Handle
 */
Handle::Handle(): u(new int(1)), p(new Point) { }
Handle::Handle(int x, int y): u(new int(1)), p(new Point(x, y)) { }
Handle::Handle(const Point& p0): u(new int(1)), p(new Point(p0)) { }
Handle::Handle(const Handle& h): u(h.u), p(h.p) { ++*u; }

Handle&
Handle::operator = (const Handle& h)
{
    ++*h.u;
    if(--*u == 0)
    {
        delete u;
        delete p;
    }

    u = h.u;
    p = h.p;
    return *this;
}

int Handle::x() const { return p->x(); }
int Handle::y() const { return p->y(); }

Handle& Handle::x(int x0)
{
    p->x(x0);
    return *this;
}

Handle& Handle::y(int y0)
{
    p->y(y0);
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
