#ifndef _BASE_PAGE_H_
#define _BASE_PAGE_H_
#include <iostream>
using std::cout;
using std::endl;

class BasePage {
    public:

        void header();
        void footer();
        void lefter();
        virtual void content()=0;
};
#endif
