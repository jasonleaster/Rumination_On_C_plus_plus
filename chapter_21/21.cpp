template<class X, class Y>
class Comp_base
{
    public:
        virtual Y operator() (X) const = 0;
        virtual Comp_base* clone() const = 0;
        virtual ~Comp_base() { }
};

template<class F, class G, class X, class Y>
class Comp: public Comp_base<X, Y>
{
    public:
        Comp(F f0, G g0): f(f0), g(g0) { }

        Y operator() (X x) const { return f(g(x));}

        Comp_base<X, Y>* clone() const
        {
            return new Comp(*this);
        }

    private:
        F f;
        G g;
};

template<class X, class Y>
class Composition
{
    public:
        template<class F, class G> Composition(F f, G g):
            p(new Comp<F, G, X, Y> (f, g)) { }

        Composition(const Composition& c):
            p(c.p->clone()) { }

        Composition& operator = (const Composition&)
        {
            if(this != &c)
            {
                delete p;
                p = c.p->clone();
            }
            return *this;
        }

        ~Composition() { delete p;};
        Y operator() (X x) const
        {
            return (*p)(x);
        }

    private:
        Comp_base<X, Y>* p;
};

extern int f(int);
extern int g(int);
extern int h(int);

int main()
{
    Composition<int ,int> fg(f, g);
    Composition<int ,int> fgh(fg, h);

}
