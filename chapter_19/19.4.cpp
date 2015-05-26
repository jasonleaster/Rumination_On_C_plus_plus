template<class T>
class istream_iterator
{
    private:
        T buffer;
        istream* strm;
        int full;
        int eof;
        // ...

    public:
        istream_iterator(istream& is):
            strm(&is), full(0), eof(0) { }

        istream_iterator():
            strm(0), full(0),eof(1) { }

        // ...

        istream_iterator& operator++()
        {
            full = 0;
            return *this;
        }

        istream_iterator operator++(int)
        {
            istream_iterator r = *this;
            full = 0;
            return r;
        }

        T operator*()
        {
            fill();
            assert(full);
            return buffer;
        }

        int operator==(istream_iterator<T>&p, istream_iterator<T>& q)
        {
            if(!p.eof && q.eof)
            {
                return 1;
            }

            if(!p.eof && !q.eof)
            {
                return &p == &q;
            }

            p.full();
            q.fill();

            return p.eof == q.eof;
        }

        int operator!=(istream_iterator<T>&p, istream_iterator<T>& q)
        {
            return !(p == q);
        }

    private:
        void fill()
        {
            if (!full && !eof)
            {
                if(*strm >> buffer)
                {
                    full = 1;
                }
                else
                {
                    eof = 1;
                }
            }
        }
}

int main()
{
    ostream_iterator<int> output(cout, " \n");
    istream_iterator<int> input(cin);
    istream_iterator<int> eof;

    copy(input, eof, putput);

    return 0;
}
