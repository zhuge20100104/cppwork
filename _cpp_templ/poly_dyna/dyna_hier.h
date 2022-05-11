#ifndef _FREDRIC_DYNA_HIER_H_
#define _FREDRIC_DYNA_HIER_H_

#include "coord.h"

class geo_obj {
    public:
        // 纯虚函数，绘制图形
        virtual void draw() const = 0;
        // 纯虚函数，获取重心
        virtual coord center_of_gravity() const = 0;
};

class circle: public geo_obj {
    public:
        circle(coord const& center, int radius);
        virtual void draw() const;
        virtual coord center_of_gravity() const;
    
    private:
        coord center_;
        int radius_;
};

class line: public geo_obj {
    public:
        line(coord const& start, coord const& end);
        virtual void draw() const;
        virtual coord center_of_gravity() const;
    
    private:
        coord start_;
        coord end_;
};
#endif