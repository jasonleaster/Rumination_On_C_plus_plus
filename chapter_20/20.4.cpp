template<class It, class T>
class Rev
{
    friend bool operator == (const Rev<It, T>, const Rev<It, T>)
    {
        return x.it == y.it;
    }

    friend bool operator != (const Rev<It, T>, const Rev<It, T>)
    {
        return x.it != y.it;
    }

    public:
        Rev() { };
        Rev(It, i): it(i) { };
        operator It() { return it;}

        Rev<It, T>& operator ++() { --it; return *this;}
        Rev<It, T>& operator --() { ++it; return *this;}

        Rev<It, T>& operator ++(int)
        {
            Rev<It, T> r = *this;
            --it;
            return r;
        }

        Rev<It, T>& operator --(int)
        {
            Rev<It, T> r = *this;
            ++it;
            return r;
        }

        T& operator*()
        {
            It i = it;
            --i;
            return *i;
        }

    private:
        It it;
};
