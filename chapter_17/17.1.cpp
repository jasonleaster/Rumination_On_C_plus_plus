const int*
find1(const int* array, int n, int x)
{
    const int* p = array;
    for(int i = 0; i < n; i++)
    {
        if(*p == x)
        {
            return p;
        }

        ++p;
    }

    return 0;
}
