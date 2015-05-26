template<class P, class T>
void reverse(P start, P beyond)
{
    while(start < beyond)
    {
        T t = *start;
        --beyond;
        *start = *beyond;
        *beyond = t;
        ++start;
    }
}

template<class P, class T>
void reverse2(P start, P beyond)
{
    while(start != beyond)
    {
        --beyond;
        if(start != beyond)
        {
            T t = *start;
            *start = *beyond;
            *beyond = t;
            ++start;
        }
    }
}
