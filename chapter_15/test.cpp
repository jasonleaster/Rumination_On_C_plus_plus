#include "seq.h"

int main()
{
    Seq<int> s;

    for (int i = 0; i < 10; i++)
    {
        s.insert(i);
    }

    cout << "length of Seq @s: " << s.length() << endl;

    cout << s << endl;

    s.flip();
    cout << s << endl;

 //   s = merge(s, s);
    cout << s.tl() << endl;

    return 0;
}
