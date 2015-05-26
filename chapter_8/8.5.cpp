/*
    Programmer  :   EOF
    Date        :   2015.05.19
    File        :   8.5.cpp
    E-mail      :   jasonleaster@gmail.com

 */
#include <iostream>
#include <string>

using namespace std;


/*
   This @Expr_node is the base-class.
 */
class Expr_node
{
    friend ostream& operator << (ostream&, const Expr_node&);
    friend class Expr;

    int use;// @use is a counter to avoid copying objects.

    protected:
        Expr_node(): use(1) { }
        virtual void print(ostream&) const = 0;
        virtual ~Expr_node() { }
        virtual int eval() const = 0;
};


class Expr
{
    friend ostream& operator<<(ostream&, const Expr&);
    Expr_node* p;

    public:
        Expr():p(NULL){}
        Expr(int);
        Expr(const string&, Expr);
        Expr(const string&, Expr, Expr);
        Expr(const string&, Expr, Expr, Expr);
        Expr(const Expr& t) { p = t.p; ++p->use; };

        Expr& operator=(const Expr&);

        ~Expr() { if(--p->use == 0) delete p;}

        int eval() const {return p->eval();}
};

ostream&
operator<<(ostream& o, const Expr_node& e)
{
    e.print(o);
    return o;
}

Expr&
Expr::operator=(const Expr& rhs)
{
    rhs.p->use++;
    if(--p->use == 0)
    {
        delete p;
    }

    p = rhs.p;
    return *this;
}

ostream&
operator<<(ostream& o, const Expr& t)
{
    o << (*t.p);
    return o;
}

class Int_node: public Expr_node
{
    friend class Expr;

    int n;

    Int_node(int k): n(k) { }
    void print(ostream& o) const { o << n;}
    int eval() const { return n;}
};

class Unary_node: public Expr_node
{
    friend class Expr;
    string op;
    Expr opnd;
    Unary_node(const string& a, Expr b):
        op(a), opnd(b) { }

    void print(ostream& o) const
    {
        o << "(" << op << opnd << ")";
    }

    int eval() const
    {
        if(op == "-")
        {
            return -opnd.eval();
        }

        throw "error, bad op" + op + "int UnaryNode";
    }
};

class Binary_node: public Expr_node
{
    friend class Expr;
    string op;

    Expr left;
    Expr right;

    Binary_node(const string& a, Expr b, Expr c):
        op(a), left(b), right(c) { }

    void print(ostream& o) const
    {
        o << "(" << left << op << right << ")";
    }

    int eval() const
    {
        int op1 = left.eval();
        int op2 = right.eval();

        if(op == "-") return op1 - op2;
        if(op == "+") return op1 + op2;
        if(op == "*") return op1 * op2;
        if(op == "/") return op1 / op2;

        if(op == "/" && op2 != 0) return op1/ op2;

        throw "error, bad op" + op + "int BinaryNode";
    }
};

class Ternary_node:public Expr_node
{
    friend class Expr;

    string op;
    Expr left;
    Expr middle;
    Expr right;

    Ternary_node(const string& a, Expr b, Expr c, Expr d):
        op(a), left(b), middle(c), right(d) { }
    void print(ostream& o) const;
    int eval() const;
};

void Ternary_node::print(ostream& o) const
{
    o << "(" << left << " ? " << middle << ":" << right << ")";
}

int Ternary_node::eval() const
{
    if(left.eval())
    {
        return middle.eval();
    }
    else
    {
        return right.eval();
    }
}

Expr::Expr(int n)
{
    p = new Int_node(n);
}

Expr::Expr(const string& op, Expr t)
{
    p = new Unary_node(op, t);
}

Expr::Expr(const string& op, Expr left, Expr right)
{
    p = new Binary_node(op, left, right);
}

Expr::Expr(const string& op, Expr left, Expr middle, Expr right)
{
    p = new Ternary_node(op, left, middle, right);
}

int main()
{
    Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
    cout << t << " = " << t.eval() << endl;
    t = Expr("*", t, t);
    cout << t << " = " << t.eval() << endl;

    t = Expr("?",Expr(1),Expr(2),Expr(3));
    cout << t << " = " << t.eval() << endl;
    return 0;
}
