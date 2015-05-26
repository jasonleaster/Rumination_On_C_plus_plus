#include <iostream>

using namespace std;

int sum(int *p, int n)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        result += p[i];
    }

    return result;
}

int main()
{
    int x[10];

    for(int i = 0; i < 10; i++)
    {
        x[i] = i;
    }

    cout << sum(x, 10) << endl;

    return 0;
}
