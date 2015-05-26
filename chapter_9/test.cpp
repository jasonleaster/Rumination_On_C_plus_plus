#include "picture.h"

using namespace std;

char* init[] = {"Paris", "in the", "Spring"};

int main()
{
    Picture p(init, 3);
    cout << p << endl;

    p = frame(p);
    cout << p << endl;

    p = p & p;
    cout << p << endl;


    p = p | p;
    cout << p << endl;

    Picture q(init,2);

    cout << q << endl;
    return 0;
}
