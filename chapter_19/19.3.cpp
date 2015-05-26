template<class T>
class ostream_iterator
{
    public:
        ostream_iterator(ostream& os, const char* s):
            strm(&os), str(s)
        { }

        ostream_iterator& operator++() { return *this;}
        ostream_iterator& operator++(int) { return *this;}
        ostream_iterator& operator*() { return *this;}

        ostream_iterator& operator= (const T& t)
        {
            *strm << t << str;
            return *this;
        }

    private:
        ostream* strm;
        const char* str;

}

int main()
{
    ostream_iterator<int> oi(cout, " \n");
    Constant_iterator c(42);

    copy(c, c+10, oi);
    return 0;
}
