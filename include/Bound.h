#ifndef BOUND_H
#define BOUND_H

// To define the bounds of objects, e.g. backgrounds
// what mouse position is in bound / not in bound

class Bound {
public:
    float x_ubound; // upper bound x value (e.g. far right)
    float x_lbound; // " lower bound
    float y_ubound; // upper bound y value (e.g. top)
    float y_lbound; // " lower bound
    
    // is input x,y within bounds?
    bool inBounds( int x, int y ) {
        return x < x_ubound && 
           x > x_lbound && 
           y < y_ubound && 
           y > y_lbound;
    }
};

#endif