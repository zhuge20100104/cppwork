#include <boost/function.hpp>

typedef boost::function<void(int)> fobject_t;

void process_integers(const fobject_t& f);

void my_ints_function(int i);

int main(int argc, char* argv[]) {
    process_integers(&my_ints_function);
}

void my_ints_function(int /*i*/) {

}

void process_integers(const fobject_t& f) {
    f(10);
}

