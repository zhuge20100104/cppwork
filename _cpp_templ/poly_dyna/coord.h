#ifndef _FREDRIC_COORD_H_
#define _FREDRIC_COORD_H_

#include <cstdlib>

class coord {
        
    public:
        int x, y;
        
        coord(int i1, int i2): x{i1}, y{i2} {}

        friend coord operator-(coord const& c1, coord const& c2) {
            return coord(c1.x - c2.x, c1.y - c2.y);
        }

        coord abs() {
            return coord(std::abs(x), std::abs(y));
        }
};

#endif