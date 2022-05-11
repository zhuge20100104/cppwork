#include <iostream>
#include <cstdlib>

struct point {
    int x;
    int y;
};


void draw_line(int x1, int y1, int x2, int y2) {
    std::cout << "Start: (" << x1 << " " << y1 << ")" << std::endl; 
    std::cout << "End  : (" << x2 << " " << y2 << ")" << std::endl; 
}

void draw_line(point const& start, point const& end) {
    std::cout << "Start: (" << start.x << " " << start.y << ")" << std::endl; 
    std::cout << "End  : (" << end.x << " " << end.y << ")" << std::endl; 
}

int main(int argc, char* argv[]) {
    draw_line(1, 1, 2, 2);
    draw_line({1, 1}, {2, 2});
    
    return EXIT_SUCCESS;
}