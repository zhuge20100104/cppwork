#ifndef _FREDRIC_PROPERTY_PROXY_HPP_
#define _FREDRIC_PROPERTY_PROXY_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <memory>

struct Image {
    virtual void draw() = 0;
};

struct Bitmap: Image {
    Bitmap(std::string const& file_name) {
        std::cout << "Loading bitmap from " << file_name << "\n";
    }

    void draw() override {
        std::cout << "Drawing bitmap\n"; 
    }
};

struct LazyBitmap: Image {
    LazyBitmap(std::string const& file_name_): file_name{file_name_} {
    }

    void draw() override {
        if(!bmp) {
            bmp = std::make_unique<Bitmap>(file_name);
        }
        bmp->draw();
    }
private:
    std::string file_name;
    std::unique_ptr<Bitmap> bmp{nullptr};
};
#endif