struct Node
{
    string value;
    Node* next;
};

Node* listfind(Node* p, const string& x)
{
    while(p && *p != x)
    {
        p = p->next;
    }
    
    return p;
}

class Nodep
{
    public:
        Nodep(Node* p): pt(p) { }
        string& operator*() { return pt->value; }

        void operator++() { pt = pt->next;}
        friend int operator == (const Nodep&, const Nodep&);
        friend int operator != (const Nodep&, const Nodep&);

    private:
        Node* pt;
};

int operator == (const Nodep& p, const Nodep& q)
{
    return p.pt == q.pt;
}

int operator != (const Nodep& p, const Nodep& q)
{
    return p.pt != q.pt;
}

Node* listfind(Node* p, const string& x)
{
    return find6(Nodep(p), Nodep(0), x);
}
