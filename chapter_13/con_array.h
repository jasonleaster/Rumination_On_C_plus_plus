/**************************************************
    Programmer  :   EOF
    File        :   con_array.h
    Date        :   2015.05.25
    E-mail      :   jasonleaster@gmail.com

 **************************************************/
#ifndef _CON_ARRAY_H
#define _CON_ARRAY_H

#include <iostream>

using namespace std;

template <class T> class Array;
template <class T> class Pointer;
template <class T> class Array_data;
template <class T> class Ptr_to_const;

template <class T>
class Array_data
{
    friend class Array<T>;
    friend class Pointer<T>;
    friend class Ptr_to_const<T>;

    Array_data(unsigned size = 0):
        data(new T[size]), sz(size), use(1) { }

    ~Array_data() { delete [] data;}

    void resize(unsigned n);
    void copy(T* arr, unsigned n);
    void grow(unsigned new_sz);
    void clone(Array_data<T> const &a, unsigned n);

    Array_data(const Array_data& d): data(d.data), sz(d.sz), use(d.use) {}

    const T& operator[](unsigned n) const
    {
        if (n >= sz)
        {
            throw "Array subscript out of range";
        }

        return data[n];
    }

    T& operator[](unsigned n)
    {
        if (n >= sz)
        {
            throw "Array subscript out of range";
        }

        return data[n];
    }

    /*
       The real data that the container maintained is stored in @data
     */
    T* data;
    unsigned sz;
    int use;
};


template<class T>
class Array
{
    friend class Pointer<T>;

    friend ostream& operator << (ostream& o, const Array<T> &a)
    {
        for (int i = 0; i < a.size(); i++)
        {
            o << " " << a[i];
        }

        return o;
    }

    public:
        Array(unsigned size):
            data(new Array_data<T>(size)) { }

        Array(const Array& a):
            data(new Array_data<T>(a.data->sz))
        {
            data->copy(a.data->data, a.data->sz);
        }

        ~Array()
        {
            if(--data->use == 0)
            {
                delete data;
            }
        }

        /*
           We overload the operator @[]. One is used for right value which
           is read-only. The other is used for left value which is a 
           reference.
         */
        const T& operator[](unsigned n) const
        {
            return (*data)[n];
        }

        T& operator[](unsigned n)
        {
            return (*data)[n];
        }

        void resize(unsigned n)
        {
            data->resize(n);
        }

        int size(void) const
        {
            return data->sz;
        }

        void reserve(unsigned new_sz)
        {
            if(new_sz >= data->sz)
            {
                data->grow(new_sz);
            }
        }

        Array& operator=(const Array& a)
        {
            if(this != &a)
            {
                data->clone(*(a.data), a.data->sz);
            }

            return *this;
        }


    private:
        Array_data<T>* data;
};


template<class T>
class Ptr_to_const
{
    public:
        // const Array& but not Array&
        Ptr_to_const(const Array<T>& a, unsigned n = 0):
            ap(a.data),
            sub(n) { ++ap->use; }

        Ptr_to_const() : ap(0), sub(0) { }
        Ptr_to_const(const Ptr_to_const<T>& p):
            ap(p.ap), sub(p.sub)
        {
            if(ap)
            {
                ++ap->use;
            }
        }

        ~Ptr_to_const()
        {
            if(ap && --ap->use == 0)
            {
                delete ap;
            }
        }

        Ptr_to_const& operator=(const Ptr_to_const<T>& p)
        {
            if(p.ap)
            {
                ++p.ap->use;
            }

            if(ap && --ap->use == 0)
            {
                delete ap;
            }

            ap = p.ap;
            sub = p.sub;
            return *this;
        }

        // return const T& but not T&
        const T& operator*() const
        {
            if(ap == 0)
            {
                throw "* of unbound Ptr_to_const";
            }

            return *this;
        }

    private:
        Array_data<T>* ap;
        unsigned sub;
};

template<class T>
class Pointer: public Ptr_to_const<T>
{
    public:
        Pointer(Array<T>& a, unsigned n = 0):
            ap(a.data), sub(n) { ++ap->use;}

        Pointer(): ap(0), sub(0) { }

        Pointer(const Pointer<T>& p): ap(p.ap), sub(p.sub)
        {
            if(ap)
            {
                ++ap->use;
            }
        }

        ~Pointer()
        {
            if(ap && --ap->use == 0)
            {
                delete ap;
            }
        }

        Pointer& operator=(const Pointer<T>& p)
        {
            if(p.ap)
            {
                ++p.ap->use;
            }

            if(ap && --ap->use == 0)
            {
                delete ap;
            }

            ap = p.ap;
            sub = p.sub;
            return *this;
        }

        T& operator*() const
        {
            if (ap == 0)
            {
                throw "* of unbound Pointer";
            }

            return (*ap)[sub];
        }

    private:
        Array_data<T>* ap;
        unsigned sub;
};

/*
   The member function in @class-Array_data
 */
template<class T>
void Array_data<T>::resize(unsigned n)
{
    if (n == sz)
    {
        return;
    }

    T* odata = data;
    data = new T[n];
    copy(odata, sz > n ? n : sz);
    delete [] odata;
    sz = n;
}

template<class T>
void Array_data<T>::copy(T* arr, unsigned n)
{
    for (int i = 0; i < n; i++)
    {
        data[i] = arr[i];
    }
}

template<class T>
void Array_data<T>::grow(unsigned new_sz)
{
    unsigned nsz = sz;
    if(nsz == 0)
    {
        nsz = 1;
    }

    while(nsz <= new_sz)
    {
        nsz *= 2;
    }

    resize(nsz);
}

template<class T>
void Array_data<T>::clone(Array_data<T> const &a, unsigned n)
{
    delete [] data;
    data = new T[sz = a.sz];
    copy(a.data, sz);
}

#endif
