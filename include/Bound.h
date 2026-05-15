class Bound {
public:
    float x_ubound;
    float x_lbound;
    float y_ubound;
    float y_lbound;
    
    bool inBounds(int x, int y) {
        return x < x_ubound && 
           x > x_lbound && 
           y < y_ubound && 
           y > y_lbound;
    }
};