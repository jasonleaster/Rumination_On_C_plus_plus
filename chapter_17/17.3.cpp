template<class T>
T* find3(T* array, T* beyond, const T& x)
{
    T* p = array;
    while(p != beyond)
    {
        if(*p == x)
        {
            return p;
        }

        ++p;
    }

    return 0;
}

template<class T>
T* find4(T* array, T* beyond, const T& x)
{
    T* p = array;
    while(p != beyond)
    {
        if(*p == x)
        {
            return p;
        }

        ++p;
    }

    return beyond;
}

template<class T>
T* find5(T* array, T* beyond, const T& x)
{
    T* p = array;
    while(p != beyond && *p != x)
    {
        ++p;
    }

    return p;
}
