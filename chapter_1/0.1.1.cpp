#include <stdio.h>

class Trace
{
    public:
        Trace() {noisy = 0;}
        void print(char *s)
        {
            if (noisy) printf("%s", s);
        }

        void on()
        {
            noisy = 1;
        }

        void off()
        {
            noisy = 0;
        }

    private:
        int noisy;
};
