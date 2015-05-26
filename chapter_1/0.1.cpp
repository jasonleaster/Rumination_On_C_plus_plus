#include <stdio.h>

class Trace
{
    public:
        void print(char *s) {printf("%s", s); }
};

int main()
{
    Trace t;
    t.print("begin main()\n");

    // the body of main function

    t.print("end main()\n");
}
