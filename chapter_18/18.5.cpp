template<class Iter, class Function>
void apply(Iter start, Iter beyond, Function t)
{
    while(start != beyond)
    {
        *start = f(*start);
        ++start;
    }
}
