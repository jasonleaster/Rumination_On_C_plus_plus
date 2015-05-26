/**********************************************
Programmer  :   EOF
Date        :   2015.05.18
File        :   5.4.cpp
E-mail      :   jasonleaster@gmail.com

***********************************************/
#include <iostream>

class Vehicle
{
    public:
        /*
           It will be OK, if you don't use virtual function.
        double weight() const;
        void start();
        */

        virtual double weight() const = 0;
        virtual void start() = 0;
        virtual Vehicle* copy() const = 0;
        virtual ~Vehicle() { } ;       
        // ...
};

class RoadVehicle: public Vehicle {/* ... */};
class AutoVehicle: public RoadVehicle {/* ... */};
class Aircraft: public Vehicle {/* ... */};
class Helicopter: public Aircraft {/* ... */};


class VehicleSurrogate
{
    public:
        /*
           Constructor
         */
        VehicleSurrogate();
        VehicleSurrogate(const Vehicle&);
        VehicleSurrogate(const VehicleSurrogate&);

        /*
           De-constructor
         */
        ~VehicleSurrogate();

        VehicleSurrogate& operator =(const VehicleSurrogate&);

        /*
           Operations from class Vehicle
         */
        double weight() const;
        void start();

        // ...

    private:
        Vehicle* vp;
};

VehicleSurrogate::VehicleSurrogate(): vp(0) { }
VehicleSurrogate::VehicleSurrogate(const Vehicle& v):
    vp(v.copy()) { }

VehicleSurrogate:: ~VehicleSurrogate()
{
    delete vp;
}

VehicleSurrogate::VehicleSurrogate (const VehicleSurrogate& v):
    vp(v.vp ? v.vp->copy() : 0) { }

VehicleSurrogate&
VehicleSurrogate::operator=(const VehicleSurrogate& v)
{
    if (this != &v)
    {
        delete vp;
        vp = (v.vp ? v.vp->copy() : 0);
    }

    return *this;
}

double VehicleSurrogate::weight() const
{
    if (vp == 0)
    {
        throw "empty VehicleSurrogate.weight()";
    }

    return vp->weight();
}

void VehicleSurrogate::start()
{
    if (vp == 0)
    {
        throw "empty VehicleSurrogate.start()";
    }

    vp->start();
}


class Automobile: public AutoVehicle
{
        double weight() const;
        void start();
        Vehicle* copy() const;
};

double
Automobile::weight() const
{
    return 0.0;
}

void
Automobile::start()
{
    std::cout << "Hello this is automobile" << std::endl;
}

Vehicle*
Automobile::copy() const
{
    return new Automobile(*this);
}



/*
   Here is our test unit.

   Attention! 
   Never use assignment between class objects out of function block.
   If your assignment operation is not in function block, you must got 
   an error from compiler.

   But it's ok, if you would like to define the varibles outside of blocks.
 */

VehicleSurrogate parking_lot[1000];

Automobile x;

int num_vehicles = 0;

int main()
{
    /*
       These two assignment statement are doing the same thing.
     */
    parking_lot[num_vehicles++] = x;

    //parking_lot[num_vehicles++] = VehicleSurrogate(x);

    return 0;
}

