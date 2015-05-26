#include <iostream>

using namespace std;

template<class T>
class Iterator
{
    public:
        Iterator(T *p, int c): data(p), len(c) { }
        ~Iterator(){ }

        int valid() const
        {
            return len > 0;
        }

        T next()
        {
            --len;
            return *data++;
        }

    private:
        T* data;
        int len;
};

int sum(Iterator<int> ir)
{
    int result = 0;

    while(ir.valid())
    {
        result += ir.next();
    }

    return result;
}

int sum(int *p, int n)
{
    return sum(Iterator<int>(p, n));
}

int main()
{
    int x[10];

    for(int i = 0; i < 10; i++)
    {
        x[i] = i;
    }

    cout << sum(Iterator<int>(x, 10)) << endl;

    return 0;
}
