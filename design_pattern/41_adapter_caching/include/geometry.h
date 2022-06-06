#ifndef _FREDRIC_GEOMETRY_H_
#define _FREDRIC_GEOMETRY_H_

#include <boost/functional/hash.hpp>

struct Point {
    int x, y;

    friend std::size_t hash_value(Point const& obj) {
        std::size_t seed = 0x725C686F;
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        return seed;
    }
};

struct Line {
    Point start, end;

    friend std::size_t hash_value(Line const& obj) {
        std::size_t seed = 0x719E6B16;
        boost::hash_combine(seed, obj.start);
        boost::hash_combine(seed, obj.end);
        return seed;
    }
};

struct VectorObject {
    virtual std::vector<Line>::iterator begin() = 0;
    virtual std::vector<Line>::iterator end() = 0;
};

struct VectorRectangle: VectorObject {
    VectorRectangle(int x, int y, int width, int height) {
        lines.emplace_back(Line{Point{x, y}, Point{x+width, y}});
        lines.emplace_back(Line{Point{x+width, y}, Point{x+width, y+height}});
        lines.emplace_back(Line{Point{x, y}, Point{x, y+height}});
        lines.emplace_back(Line{Point{x, y+height}, Point{x+width, y+height}});
    }

    std::vector<Line>::iterator begin() {
        return lines.begin();
    }

    std::vector<Line>::iterator end() {
        return lines.end();
    }

private:
    std::vector<Line> lines;
};
#endif