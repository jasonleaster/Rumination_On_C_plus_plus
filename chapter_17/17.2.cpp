template<class T>
T* find2(T* array, int n, const T& x)
{
    T* p = array;
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
