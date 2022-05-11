#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <memory>

using std::cout;
using std::endl;

using namespace boost::asio;

using ErrorCode = boost::system::error_code;


void print(const ErrorCode& ec, deadline_timer* t, int *count) {
    if(*count < 5) {
        cout << *count << endl;
        
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        
        t->async_wait(
                [t, count](const auto& err) {
                    print(err, t, count);
                }
                );
    }
}

std::shared_ptr<deadline_timer> registerTimer(io_service& io, int *count) {
    auto t = std::make_shared<deadline_timer>(io, boost::posix_time::seconds(1));
    auto pt = t.get();
    t->async_wait(
            [pt, count] (const auto& err) {
                print(err, pt, count);
            }
            );
    return t;
}

int main(void) {
    
    io_service io;

    int count = 0;
    
    auto t = registerTimer(io, &count);
    t.reset();   // C++的阴暗面，此时t已经失效，野指针，但是程序仍然能跑
    io.run();
    
    cout << "Final count is: " << count << endl;

    return 0;
}

