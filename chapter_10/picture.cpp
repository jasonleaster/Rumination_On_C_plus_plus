/********************************************************
    Programmer  :   EOF
    File        :   picture.cpp
    Date        :   2015.05.24
    E-mail      :   jasonleaster@gmail.com

 *******************************************************/

#include "picture.h"

/*
   Member function of @class-P_Node
 */
int P_Node::max(int x, int y) const
{
    return x > y ? x : y;
}

/*
   Member function of @class-Picture
 */
Picture::Picture(const char* const *str, int n):
        p(new String_Pic(str, n))
{
}

Picture::Picture(const Picture& orig):p(orig.p)
{
    orig.p->use++;
}

Picture::~Picture()
{
    if(--p->use == 0)
    {
        delete p;
    }
}

Picture&
Picture::operator=(const Picture& orig)
{
    orig.p->use++;
    if(--p->use == 0)
    {
        delete p;
    }

    p = orig.p;

    return *this;
}

int Picture::height() const
{
    return p->height();
}

int Picture::width() const
{
    return p->width();
}

void Picture::display(ostream& o, int x, int y) const
{
    p->display(o, x, y);
}

ostream&
operator << (ostream& os, const Picture& p)
{
    int ht = p.height();
    int wd = p.width();

    for(int i = 0; i < ht; i++)
    {
        p.display(os, i, wd);
        os << endl;
    }

    return os;
}


/*
   Member function of @class-String_Pic
 */
String_Pic::String_Pic(const char* const *p, int n):
    data(new char* [n]), size(n)
{
    for(int i = 0; i < n; i++)
    {
        data[i] = new char[strlen(p[i] + 1)];
        strcpy(data[i], p[i]);
    }
}

String_Pic::~String_Pic()
{
    for(int i = 0; i < size; i++)
    {
        delete [] data[i];
    }
    delete [] data;
}

int String_Pic::height() const
{
    return size;
}

int String_Pic::width() const
{
    int n = 0;

    for(int i = 0; i < size; i++)
    {
        n = max(n, strlen(data[i]));
    }
    return n;
}

static void pad(ostream& os, int x, int y)
{
    for (int i = x; i < y; i++)
    {
        os << " ";
    }
}

void String_Pic::display(ostream& os, int row, int width) const
{
    int start = 0;

    if(row >= 0 && row < height())
    {
        os << data[row];
        start = strlen(data[row]);
    }

    pad(os, start, width);
}


/*
   Member function of @class-Frame_Pic
 */
Frame_Pic::Frame_Pic(const Picture& pic): 
    p(pic) 
{ }

int Frame_Pic::height() const
{
    return p.height() + 2;
}

int Frame_Pic::width() const
{
    return p.width() + 2;
}

void Frame_Pic::display(ostream& os, int row, int wd) const
{
    if(row < 0 || row >= height())
    {
        //run-across ??
        pad(os, 0, wd);
    }
    else
    {
        if(row == 0 || row == height() -1)
        {
            os << "+";
            int i = p.width();
            while(--i >= 0)
            {
                os << "-";
            }

            os << "+";
        }
        else
        {
            os << "|";
            p.display(os, row - 1, p.width());
            os << "|";
        }
        pad(os, width(), wd);
    }
}

Picture frame(const Picture& pic)
{
    return new Frame_Pic(pic);
}

/*
   Member functions of @class-VCat_Pic
 */
VCat_Pic::VCat_Pic(const Picture& t, const Picture& b):
        top(t), bottom(b) 
{ }

int VCat_Pic::height() const
{
    return top.height() + bottom.height();
}

int VCat_Pic::width() const
{
    return max(top.width(), bottom.width());
}

void VCat_Pic::display(ostream& os, int row, int wd) const
{
    if(row >= 0 && row < top.height())
    {
        top.display(os, row, wd);
    }
    else if(row < top.height() + bottom.height())
    {
        bottom.display(os, row-top.height(), wd);
    }
    else
    {
        pad(os, 0, wd);
    }
}

Picture operator & (const Picture& t, const Picture& b)
{
    return new VCat_Pic(t, b);
}

/*
   Member functions of @class-HCat_Pic
 */

HCat_Pic::HCat_Pic(const Picture& l, const Picture& r): left(l), right(r) {}

int HCat_Pic::height() const
{
    int n = max(left.height(), right.height());
    return n;
}

int HCat_Pic::width() const
{
    return left.width() + right.width();
}

void HCat_Pic::display(ostream& os, int row, int wd) const
{
    left.display(os, row, left.width());
    right.display(os, row, right.width());
    pad(os, width(), wd);
}

Picture operator | (const Picture& l, const Picture& r)
{
    return new HCat_Pic(l, r);
}

