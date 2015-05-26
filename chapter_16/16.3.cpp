#include <iostream>

using namespace std;

class Int_iterator
{
    public:
        Int_iterator(int *p, int c): data(p), len(c) { }
        ~Int_iterator(){ }

        int valid() const
        {
            return len > 0;
        }

        int next()
        {
            --len;
            return *data++;
        }

        Int_iterator(const Int_iterator&);
        Int_iterator& operator=(const Int_iterator&);

    private:
        int* data;
        int len;
};


int sum(Int_iterator ir)
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
    return sum(Int_iterator(p, n));
}

int main()
{
    int x[10];

    for(int i = 0; i < 10; i++)
    {
        x[i] = i;
    }

    cout << sum(Int_iterator(x, 10)) << endl;

    return 0;
}
