/*******************************************************
Programmer  :   EOF
Date        :   2015.05.22
File        :   picture.h
E-mail      :   jasonleaster@gmail.com

Description:
    Here is a demo in << Ruminations on C++ >>.

*******************************************************/

#include <iostream>
#include <string.h>

using namespace std;

class Picture
{
    /*
       All implementation of member function and friend functions
       could be found in "picture.cpp"
     */
    friend ostream& operator<<(ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture operator & (const Picture&, const Picture&);
    friend Picture operator | (const Picture&, const Picture&);

    public:
        Picture(): height(0), width(0), data(0) { }
        Picture(const char* const*, int);
        Picture(const Picture&);
        ~Picture() { delete [] data; }

        Picture& operator = (const Picture&);
    
    private:
        int height;
        int width;

        char* data;
        void copyblock(int, int, const Picture&);

        /*
           This function is so cool! Don't you think so? :)
         */
        char& position(int row, int col)
        {
            return data[row * width + col];
        }

        char position(int row, int col) const
        {
            return data[row * width + col];
        }
    
        void clear(int, int, int, int);
        void init(int, int);
        static int max(int, int);
};
