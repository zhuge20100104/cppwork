#include <iostream>

enum class NewColor {Red, Green=20, Blue};

void testEnum() {
    NewColor r = NewColor::Blue;

    switch(r) {
        case NewColor::Red:
            std::cout << "red" << std::endl;
            break;
        case NewColor::Green:
            std::cout << "green" << std::endl;
            break;
        case NewColor::Blue:
            std::cout << "blue" << std::endl;
            break;
        default:
            std::cout << "What??" << std::endl;
    }
    
    int red = static_cast<int>(NewColor::Red);
    int green = static_cast<int>(NewColor::Green);
    int blue = static_cast<int>(NewColor::Blue);
    std::cout << "Red: " << red << std::endl;
    std::cout << "Green: " << green << std::endl;
    std::cout << "Blue: " <<  blue << std::endl;
  //  std::cout << NewColor::Red << std::endl;
  //  std::cout << NewColor::Green << std::endl;
  //  std::cout << NewColor::Blue << std::endl;
}

int main() {
    testEnum();
}
