template<class P, class X>
P binsearch(P start, P beyond, X x)
{
    P low = start, high = beyond;

    while(low != high)
    {
        P mid = low + (high - low)/2;
        if(x == *mid)
        {
            return mid;
        }
        else if(x < *mid)
        {
            hi = mid;
        }
        else
        {
            low = mid + 1;
        }
    }

    return beyond;
}
