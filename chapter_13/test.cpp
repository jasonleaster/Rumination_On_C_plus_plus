#include "con_array.h"

int main()
{
    Array<int> *ap = new Array<int> (10);
    Pointer<int> p(*ap, 5);
    //delete ap;

    for (int i = 0; i < 10; i++)
    {
        (*ap)[i] = i;
    }

    *p = 42;

    cout << "The size of Array " << ap->size() <<endl;
    cout << (*ap) << endl;

    ap->resize(20);
    cout << "After resize(), the size of Array " << ap->size() <<endl;
    cout << (*ap) << endl;

    return 0;
}
