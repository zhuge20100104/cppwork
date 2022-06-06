#include "promotion_array.hpp"

#include <iostream>
#include <cstdlib>

#include <boost/type_index.hpp>

int main(int argc, char* argv[]) {
    typename Promotion<char, bool>::ResultT res_t1;
    typename Promotion<Array<double>, Array<int>>::ResultT res_t2;

    std::cout << boost::typeindex::type_id_runtime(res_t1) << std::endl;
    std::cout << boost::typeindex::type_id_runtime(res_t2) << std::endl;
    
    return EXIT_SUCCESS;
}