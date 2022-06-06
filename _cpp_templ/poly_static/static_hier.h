#ifndef _FREDRIC_DYNA_HIER_H_
#define _FREDRIC_DYNA_HIER_H_

#include "coord.h"

class circle {
    public:
        circle(coord const& center, int radius);
        void draw() const;
        coord center_of_gravity() const;
    
    private:
        coord center_;
        int radius_;
};

class line {
    public:
        line(coord const& start, coord const& end);
        void draw() const;
        coord center_of_gravity() const;
    
    private:
        coord start_;
        coord end_;
};
#endif