/*****************************************************
Programmer  :   EOF
File        :   seq.h
Date        :   2015.05.26
E-mail      :   jasonleaster@gmail.com

WARNING!!

I give up to fix this program up.
It's totally shit.

I decide to rewrite it.

*****************************************************/
#ifndef _SEQ_H
#define _SEQ_H

#include <iostream>

using namespace std;

template<class T> class Seq;
template<class T> class Seq_item;

template<class T>
class Seq
{
    friend ostream& operator << (ostream& o, const Seq<T> &s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            o << " " << s.read(i);
        }

        return o;
    }

    public:
        Seq():item(0), len(0) { }
        Seq(const T& t);
        Seq(const T& t, const Seq& x);
        Seq(Seq&);
        Seq(Seq_item<T>* s, unsigned l);

        ~Seq();

        /*
            @hd() : return the first element in @Seq object which 
                    have one element at least.

            @tl() : create and return a @Seq object which copy from 
                    the object which call this function. And the first
                    element in the old object will not be copyed into
                    the new object which will be returned by @tl().
         */
        T   hd() const;
        Seq tl() const;

        int length() const;
        void destroy(Seq_item<T>* item);

        Seq<T>& flip();
        Seq<T>& insert(const T& t);

        Seq_item<T>* owntail();


        operator bool() const { return item != 0; }
        T operator*();
        Seq<T>& operator++();
        Seq<T>& operator++(int);
        Seq<T>& operator = (const Seq<T>& s);

        T read(int n) const
        {
            if(n >= len)
            {
                throw "Error, out of range";
            }

            Seq_item<T>* p = this->item;

            for (int i = 0; i < n; i++)
            {
                p = p->next;    
            }

            return p->data;
        }

    private:
        int len;
        Seq_item<T>* item;
    
};

template<class T>
Seq<T>::~Seq()
{
    destroy(item);
}

template<class T>
Seq<T>::Seq(const T& t):
    item(new Seq_item<T>(t, NULL)), len(1)
{
}

template<class T>
Seq<T>::Seq(Seq& s):
    item(s.item), len(s.len)
{
    Seq_item<T>* it = s.item;

    for(int i = 0; i < len; i++, it = it->next)
    {
        (it.use)++;
    }
}

template<class T>
Seq<T>::Seq(const T& t, const Seq& x):
    item(new Seq_item<T>(t, x.item)), len(x.len + 1)
{ 
}

template<class T>
Seq<T>::Seq(Seq_item<T>* s, unsigned l):
    item(s), len(l)
{
    if(s)
    {
        s->use++;
    }
}

template<class T>
T 
Seq<T>::hd() const
{
    if(item)
    {
        return item->data;
    }
    else
    {
        throw "hd of an empty Seq";
    }
}

template<class T>
void 
Seq<T>::destroy(Seq_item<T>* item)
{
    while(item && (--(item->use)) == 0)
    {
        Seq_item<T>* next = item->next;
        delete item;
        --(this->len);
        item = next;
    }
}

template<class T>
int 
Seq<T>::length() const
{
    return len;
}

template<class T>
Seq<T> 
Seq<T>::tl() const
{
    if(item)
    {
        return Seq<T>(item->next, len -1);
    }
    else
    {
        throw "tl of an empty Seq";
    }
}


template<class T>
class Seq_item
{
    friend class Seq<T>;

    public:
        Seq_item(const T& t, Seq_item* s);
        Seq_item(const T& t): use(1), data(t), next(0) { }

    private:
        int use;
        const T data;
        Seq_item* next;
};

template<class T>
Seq_item<T>::Seq_item(const T& t, Seq_item<T>* s):
    use(1), data(t), next(s)
{
    if(s)
    {
        s->use++;
    }
}


template<class T>
Seq<T>& 
Seq<T>::operator++()
{
    if(item)
    {
        Seq_item<T>* p = item->next;
        if(p)
        {
            p->use++;
        }

        if(--item->use == 0)
        {
            delete item;
        }

        item = p;
    }

    return *this;
}

template<class T>
Seq<T>&
Seq<T>::operator++(int)
{
    Seq<T> ret = *this;
    if(item)
    {
        --item->use;
        item = item->next;

        if(item)
        {
            item->use++;
        }
    }

    return ret;
}

template<class T>
Seq<T>& 
Seq<T>::operator = (const Seq<T>& s)
{
    Seq_item<T>* it = s.item;

    while(it)
    {
        it->use++;
    }

    destroy(item);
    item = s.item;
    len  = s.len;
    return *this;
}

template <class T> 
T 
Seq<T>::operator*()
{
    return hd();
}

template <class T>
Seq<T>& 
Seq<T>::insert(const T& t)
{
    item = new Seq_item<T>(t, item);
    (this->len)++;

    return *this;
}

template<class T>
Seq_item<T>* 
Seq<T>::owntail()
{
    if(item == 0)
    {
        return 0;
    }

    Seq_item<T>* i = item;
    Seq_item<T>** p = &item;

    while(i->use == 1)
    {
        if(i->next == 0)
        {
            return i;
        }

        p = &i->next;
        i = i->next;
    }

    *p = new Seq_item<T> (i->data);
    --i->use;
    i = i->next;

    Seq_item<T>* j = *p;

    while(i)
    {
        j->next = new Seq_item<T> (i->data);
        i = i->next;
        j = j->next;
    }

    return j;
}

template<class T> 
Seq<T>& 
Seq<T>::flip()
{
    if(item)
    {
        Seq_item<T>* k = owntail();
        Seq_item<T>* curr = item;
        Seq_item<T>* behind = NULL;

        do
        {
            Seq_item<T>* ahead = curr->next;
            curr->next = behind;
            behind = curr;
            curr = ahead;
        }while(curr);
        
        item = k;
    }

    return *this;
}

template<class T>
Seq<T> 
merge(const Seq<T>& x, const Seq<T>& y)
{
    if(!x) return y;
    if(!y) return x;

    T xh = x.hd();
    T yh = y.hd();

    if(xh < yh)
    {
        return cons(xh, merge(x.tl(), y));
    }

    return cons(yh, merge(x, y.tl()));

}

template<class T>
void split(Seq<T> x, Seq<T>& y, Seq<T>& z)
{
    while(x)
    {
        y.insert(x.hd());

        if(++x)
        {
            z.insert(x.hd());
            ++x;
        }
    }
}

template<class T> 
Seq<T> sort(const Seq<T>& x)
{
    if(!x || !x.tl())
    {
        return x;
    }

    Seq<T> p, q;

    split(x, p, q);

    return merge(sort(p), sort(q));
}

template<class T> 
Seq<T> merge2(Seq<T> x, Seq<T> y)
{
    Seq<T> r;

    while(x && y)
    {
        if(x.hd() < y.hd())
        {
            r.insert(x.hd());
            x++;
        }
        else
        {
            r.insert(y.hd());
            y++;
        }
    }

    while(x)
    {
        r.insert(x.hd());
        x++;
    }

    while(y)
    {
        r.insert(y.hd());
        y++;
    }

    r.flip();
    return r;
}

template<class T>
bool operator == (const Seq<T>& op1, const Seq<T>& op2)
{
    if(op1.length() != op2.length())
    {
        return false;
    }

    Seq_item<T>* p = op1.item;
    Seq_item<T>* q = op2.item;

    while(p != q)
    {
        assert(p != 0 && q != 0);
        
        if(*p++ != *q++)
        {
            return false;
        }
    }

    return true;
}

template<class T> 
Seq<T> cons(const T& t, const Seq<T>& s)
{
    return Seq<T>(t, s);
}

#endif
