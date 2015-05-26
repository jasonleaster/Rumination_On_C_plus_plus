template<class In, class Out>
void copy(In start, In beyond, Out result)
{
    while(start != beyond)
    {
        *result = *start;
        ++result;
        ++start;
    }
}

template<class In, class Out>
void copy(In start, In beyond, Out result)
{
    while(start != beyond)
    {
        *result++ = *start++;
    }
}
