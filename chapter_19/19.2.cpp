class Constant_iterator
{
    public:
        Constant_iterator(int = 0);
        int operator*() const;
        Constant_iterator& operator++();
        Constant_iterator& operator++(int);

    private:
        int n ;
        int count;
        friend int operator ==(const Constant_iterator&, const Constant_iterator&);
        friend int operator !=(const Constant_iterator&, const Constant_iterator&);
        friend Constant_iterator operator +(const Constant_iterator&, int);
        friend Constant_iterator operator +(int , const Constant_iterator&);
};

Constant_iterator::Constant_iterator(int k): n(k)
{
}

int Constant_iterator::operator*() const
{
    return n;
}

Constant_iterator& Constant_iterator::operator++()
{
    ++count;
    return *this;
}

Constant_iterator Constant_iterator::operator++(int)
{
    Constant_iterator r = *this;
    ++count;
    return r;
}

Constant_iterator operator + (const Constant_iterator& p, int n)
{
    Constant_iterator r = p;
    r.count += n;
    return r;
}

Constant_iterator operator + (int n, const Constant_iterator& p)
{
    return p + n;
}

int operator == (const Constant_iterator& p, const Constant_iterator& q)
{
    return p.count == q.count && p.n == q.n;
}

int operator != (const Constant_iterator& p, const Constant_iterator& q)
{
    return !(p == q);
}


