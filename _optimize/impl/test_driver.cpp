#include "test_driver.h"
#include "priority_thread.h"

#include <iostream>
#include <cstring>

//	os-independent except for PriorityThread
void test_driver(testfunc* flist, int argc, char** argv)
{
	unsigned long multiplier = 1;
	if (argc > 1) {
		if (strncmp(argv[1], "-x", 2) == 0)
			multiplier = strtoul(argv[1]+2, nullptr, 10);
	}
	if (flist == nullptr) {
		std::cout << "No test function" << std::endl;
	}
	else {
		std::cout << "multiplier set to " << multiplier << std::endl;
		PriorityThread p;
		for (unsigned f = 0; flist[f] != 0; ++f) {
			if (flist[f] == nullptr)
				continue;
			if (flist[f](1, multiplier) == 1)
				std::cout << "All tests pass" << std::endl;
			else
				std::cout << "tests failed" << std::endl;

			for (int i = 2, e = flist[f](0, multiplier); i <= e; ++i)
				if (flist[f](i, multiplier) != 1)
					std::cout << "test " << i << " failed" << std::endl;
		}
	}
}

void test_driver(testfunc f, int argc, char** argv)
{
	unsigned long multiplier = 1;
	if (argc > 1) {
		if (strncmp(argv[1], "-x", 2) == 0)
			multiplier = strtoul(argv[1]+2, nullptr, 10);
	}
	if (f == nullptr) {
		std::cout << "No test function" << std::endl;
	}
	else {
		std::cout << "multiplier set to " << multiplier << std::endl;
	    PriorityThread p;
        if (f(1, multiplier) == 1)
            std::cout << "All tests pass" << std::endl;
        else
            std::cout << "tests failed" << std::endl;

        for (int i = 2, e = f(0, multiplier); i <= e; ++i)
            if (f(i, multiplier) != 1)
				std::cout << "test " << i << " failed" << std::endl;
    }
}