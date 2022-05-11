#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

using std::cout;
using std::endl;

using namespace boost::asio;

using ErrorCode = boost::system::error_code;

void callback(const ErrorCode& ec) {
    cout << "Hello world" << endl;
}


int main(void) {
    io_service io;
    deadline_timer t(io, boost::posix_time::seconds(5));
    t.async_wait(callback);
    io.run();
    return 0;
}
