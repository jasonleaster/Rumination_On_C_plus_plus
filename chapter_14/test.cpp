#include "con_array.h"

int main()
{
    Array<int> *ap = new Array<int> (10);
    Pointer<int> p(*ap, 5);

    //delete ap;

    *p = 42;

    cout << *ap << endl;

    cout << *p << endl;

    p++;
    cout << *p << endl;

    return 0;
}
