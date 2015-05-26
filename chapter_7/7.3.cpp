/**********************************************
    Programmer  :   EOF
    Date        :   2015.05.19
    File        :   7.3.cpp
    E-mail      :   jasonleaster@gmail.com

**********************************************/
#include <iostream>

#define COW

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



class UseCount
{
    public:
        UseCount();
        UseCount(const UseCount&);
        ~UseCount();
        //another things

        bool only();
        bool reattach(const UseCount& );
        bool makeonly();

    private:
        int* p_counter;
};

UseCount::UseCount(): p_counter(new int(1)) { }

UseCount::UseCount(const UseCount& u): p_counter(u.p_counter) 
{
    ++(*p_counter); 
}

UseCount::~UseCount() 
{
    if (--(*p_counter) == 0)
    {
        delete p_counter; 
    }
}

bool UseCount::only() { return *p_counter == 1; }

bool UseCount::reattach(const UseCount& u)
{
    ++(*u.p_counter);
    if(--*p_counter == 0)
    {
        delete p_counter;
        p_counter = u.p_counter;
        return true;
    }

    p_counter = u.p_counter;
    return false;
}

bool UseCount::makeonly()
{
    if(*p_counter == 1)
    {
        return false;
    }

    --(*p_counter);
    p_counter = new int(1);

    return true;
}



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

        void show_pointer(void)
        {
            cout << p_Point << endl;
        }

    private:
        // what we added
        Point *p_Point;
        UseCount u;
};

Handle::~Handle()
{
    if (u.only())
    {
        delete p_Point;
    }
}

/*
   Constructor function of @Handle
 */
Handle::Handle(): p_Point(new Point) { }
Handle::Handle(int x, int y): p_Point(new Point(x, y)) { }
Handle::Handle(const Point& p0): p_Point(new Point(p0)) { }
Handle::Handle(const Handle& h): u(h.u), p_Point(h.p_Point) { }

Handle&
Handle::operator = (const Handle& h)
{
    if(u.reattach(h.u))
    {
        delete p_Point;
    }

    p_Point = h.p_Point;
    return *this;
}

#ifndef COW

int Handle::x() const { return p_Point->x(); }
int Handle::y() const { return p_Point->y(); }

Handle& Handle::x(int x0)
{
    p_Point->x(x0);
    return *this;
}

Handle& Handle::y(int y0)
{
    p_Point->y(y0);
    return *this;
}

#else
/*
   "Copy On Write"
 */

int Handle::x() const
{
    return p_Point->x();
}

Handle& Handle::x(int x0)
{
    if(u.makeonly())
    {
        p_Point = new Point(*p_Point);
    }

    p_Point->x(x0);
    return *this;
}

#endif

int main()
{
    Handle h(3, 4);
    Handle h2 = h;

    cout << "before rewriting" << endl;
    h.show_pointer();
    h2.show_pointer();

    h2.x(5);

    cout << "after rewriting" << endl;
    h.show_pointer();
    h2.show_pointer();

    int n = h.x();

    cout << "n = " << n << endl;
    return 0;
}
