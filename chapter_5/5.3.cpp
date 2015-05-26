class Vehicle
{
    public:
        virtual double weight() const = 0;
        virtual void start() = 0;
        virtual Vehicle* copy() = 0;
        virtual ~Vehicle() {}

        // ...
};

Vehicle* Truck:: copy() const
{
    return new Truck(*this);
}

