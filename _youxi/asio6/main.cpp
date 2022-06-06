#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

using std::cout;
using std::endl;

using namespace boost::asio;

using ErrorCode = boost::system::error_code;


void print(const ErrorCode& ec, deadline_timer* t, int *count) {
    if(*count < 5) {
        cout << *count << endl;
        
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        
        t->async_wait(boost::bind(print, placeholders::error, t, count));
    }
}


int main(void) {
    
    io_service io;

    int count = 0;

    deadline_timer t(io, boost::posix_time::seconds(1));

    t.async_wait(
            boost::bind(print, placeholders::error, &t, &count)
            );

    io.run();
    
    cout << "Final count is: " << count << endl;

    return 0;
}

