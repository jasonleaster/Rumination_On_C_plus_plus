/***********************************************
    Programmer  :   EOF
    Date        :   2015.05.22
    File        :   picture.h
    E-mail      :   jasonleaster@gmail.com

 ***********************************************/
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Picture;

class P_Node;// base class
class String_Pic;
class Frame_Pic;
class VCat_Pic;
class HCat_Pic;


class Picture
{
    friend ostream& operator<<(ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture operator& (const Picture&, const Picture&);
    friend Picture operator| (const Picture&, const Picture&);

    public:
        Picture():p(0) {} ;
        Picture(const char* const*, int);
        Picture(const Picture&);
        ~Picture();

        Picture& operator=(const Picture&);

        friend class String_Pic;
        friend class Frame_Pic;
        friend class HCat_Pic;
        friend class VCat_Pic;

    private:
        P_Node *p;

        Picture(P_Node* p_node) : p(p_node) { };

        int height() const;
        int width() const;
        void display(ostream&, int, int) const;
};

class P_Node 
{
    friend class Picture;

    protected:
        P_Node(): use(1) { };

        virtual int height() const = 0;
        virtual int width() const = 0;
        virtual void display(ostream&, int, int) const = 0;
        virtual ~P_Node() { };

        int max(int x, int y) const;

    private:
        int use;
};

class String_Pic: public P_Node 
{
    friend class Picture;

    public:
        String_Pic(const char* const*, int);
        ~String_Pic();

        int height() const;
        int width() const;
        void display(ostream&, int, int) const;

    private:
        char**data;
        int size;
};

class Frame_Pic: public P_Node 
{
    friend Picture frame(const Picture&);
    public:
        Frame_Pic(const Picture&);

        int height() const;
        int width() const;
        void display(ostream&, int, int) const;

    private:
        Picture p;
};

class VCat_Pic: public P_Node 
{
    friend Picture operator& (const Picture&, const Picture&);

    public:
        VCat_Pic(const Picture&, const Picture&);

        int height() const;
        int width() const;
        void display(ostream&, int, int) const;

    private:
        Picture top, bottom;
};

class HCat_Pic: public P_Node 
{
    friend Picture operator | (const Picture&, const Picture&);
    public:
        HCat_Pic(const Picture&, const Picture&);

        int height() const;
        int width() const;
        void display(ostream&, int, int) const;

    private:
        Picture left, right;
};

