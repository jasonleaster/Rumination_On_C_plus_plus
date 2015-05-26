/*
    Programmer  :  EOF
    Date        :  2015.05.18
    File        :  5.1.c
    E-mail      :  jasonleaster@gmail.com

 */

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
        
        // ...
};

class RoadVehicle: public Vehicle {/* ... */};
class AutoVehicle: public RoadVehicle {/* ... */};
class Aircraft: public Vehicle {/* ... */};
class Helicopter: public Aircraft {/* ... */};

Vehicle parking_lot[1000];
