#include <iostream>
#include <string>
#include <cmath>
#include <limits>

class Node {
    private:
        int size_m;
        double x0;
        double y0;
        double x1;
        double y1;
        Node** child_node;
        int coordinates_counter;
        double** coordinates;

    public:
        //Constructors:
        Node( int m, double x0, double y0, double x1, double y1 );
        //Destructor:
        ~Node();

        //Member functions:
        bool insert( double x , double y );
        bool search( double x , double y , double d );     
        void range( double xr0 , double yr0 , double xr1 , double yr1 , bool& found );
        void nearest( double x , double y );
        double* find_nearest( double x , double y );
        int num();
};