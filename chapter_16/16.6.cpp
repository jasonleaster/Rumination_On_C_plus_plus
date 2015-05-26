#include <iostream>

using namespace std;

template<class T>
class Iterator
{
    public:
        virtual int valid() const = 0;
        virtual T next() = 0;
        virtual ~Iterator(){ }

};

template<class T>
class Array_iterator: public Iterator<T>
{
    public:
        Array_iterator(T* p, int c): data(p), len(c) { }

        int valid() const { return len > 0;}

        T next()
        {
            --len;
            return *data++;
        }

    private:
        T* data;
        int len;
};

template<class T>
T sum(Iterator<T>& ir)
{
    T result = 0;

    while(ir.valid())
    {
        result += ir.next();
    }

    return result;
}

template<class T, class Iter>
void sum2(T& result, Iter ir)
{
    result = 0;
    while(ir.valid())
    {
        result += ir.next();
    }
}

template<class T> 
T sum(T* p, int n)
{
    T r = 0;
    sum2(r, Iterator<T>(p, n));
    return r;
}

int main()
{
    int x[10];

    for(int i = 0; i < 10; i++)
    {
        x[i] = i;
    }

    Array_iterator<int> it(x, 10);
    cout << sum(it) << endl;

    int r = 0;
    sum2(r, Iterator<int>(x, 10));
    cout << r << endl;
    return 0;
}
