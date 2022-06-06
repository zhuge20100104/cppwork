#ifndef _FREDRIC_RECT_DRAW_HPP_
#define _FREDRIC_RECT_DRAW_HPP_

#include "geometry.h"
#include <opencv2/opencv.hpp>

#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <vector>

std::string const window_name = "Draw Points";
using DrawableObjects = std::vector<std::shared_ptr<VectorObject>>;
using Points = std::vector<Point>;
int const EXIT_KEY = 27;

struct LineToPointAdapter {
    LineToPointAdapter(Line& line){
        static int count = 0;
        LOG(INFO) << ++count << ": Generating points for line (no caching)\n";
         // no interpolation
        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = bottom - top;

        // only vertical or horizontal lines
        if (dx == 0){
            // vertical
            for (int y = top; y <= bottom; ++y){
                points.emplace_back(Point{ left,y });
            }
            // horizontal
        } else if (dy == 0) {
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{ x, top });
            }
        }
    }

    virtual Points::iterator begin() {
        return points.begin();
    }

    virtual Points::iterator end() {
        return points.end();
    }

private:
    Points points;
};

struct Drawer {
   
    Drawer(DrawableObjects const& vector_objs_): vector_objs{vector_objs_} {
        cv::namedWindow(window_name, cv::WINDOW_NORMAL);
        cv::resizeWindow(window_name, 200, 150);
        img_ = cv::Mat::zeros(cv::Size(200, 150), CV_8UC1);
        img_.setTo(cv::Scalar(255));
        cv::imshow(window_name, img_);
        cv::setWindowProperty(window_name, cv::WND_PROP_TOPMOST, 1);
    }

    void wait_to_dispose() {
        while(EXIT_KEY != cv::waitKey(1000)) {
        }
    }

    void draw() {
        for(auto& o: vector_objs) {
            for(auto& l: *o) {
                LineToPointAdapter lpo{l};
                draw_points(lpo.begin(), lpo.end());
            }
        }
    }

private:
    DrawableObjects vector_objs;
    cv::Mat img_;

    void draw_points(Points::iterator start, Points::iterator end) {
        for(auto i=start; i!=end; ++i) {
            cv::circle(img_, cv::Point(i->x, i->y), 3, cv::Scalar(0), cv::FILLED, cv::LINE_8);
        }
        cv::imshow(window_name, img_);
    }
};
#endif