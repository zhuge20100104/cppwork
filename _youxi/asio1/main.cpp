#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using std::cout;
using std::endl;


using namespace boost::asio;


int main(void) {

    io_service io;
    deadline_timer t(io, boost::posix_time::seconds(5));
    t.wait();
    cout << "Hello world!" << endl;
    return 0;
}
