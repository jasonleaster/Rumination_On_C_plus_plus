#include "picture.h"

using namespace std;

char* init[] = {"Paris", "in the", "Spring"};

int main()
{
    Picture p(init, 3);
    cout << p << endl;

    cout << frame(p) << endl;

    cout << (frame(p) | frame(p)) << endl;

    cout << (frame(p) & frame(p)) << endl;
    
    return 0;
}
