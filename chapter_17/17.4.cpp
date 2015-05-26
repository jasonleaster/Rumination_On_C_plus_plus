template<class P, class T>
P find6(P start, P beyond, const T& x)
{
    while(start != beyond && *start != x)
    {
        ++start;
    }

    return start;
}

template<class S, class T>
S find6(S a, S b, const T& x)
{
    while(s != b && *s != x)
    {
        ++s;
    }

    return s;
}
