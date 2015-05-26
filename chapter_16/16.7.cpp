#include <iostream>

using namespace std;

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
class Reader
{
    public:
        Reader(istream& is): i(is) { advance();}
        int valid() const { return status;}

        T next()
        {
            T result = data;
            advance();
            return result;
        }

    private:
        istream& i;
        int status;
        T data;

        void advance()
        {
            i >> data;
            status = i != 0;
        }
};

int main()
{
    cout << "Enter numbers:" << endl;
    double r = 0;
    sum2(r, Reader<double>(cin));
    cout << endl;
    cout << endl;
    cout << r << endl;
    return 0;
}
