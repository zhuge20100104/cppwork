#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <vector>
using std::vector;

using std::cout;
using std::endl;

using namespace boost::asio;

using ErrorCode = boost::system::error_code;


void print(const ErrorCode& ec, std::shared_ptr<deadline_timer> t, int *count) {
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
    t->async_wait(
            [t, count] (const auto& err) {
                print(err, t, count);
            }
            );
    return t;
}

int main(void) {
    
    io_service io;

    int count = 0;

    vector<int> v {0, 1, 2, 3, 4};

    for(int i=0, size=v.size(); i<size; ++i) {
        auto t = registerTimer(io, &v[i]);
        cout << "point address is: " << t.get() << endl;
    }


    
    auto t = registerTimer(io, &count);
    io.run();
    
    for(int i=0, size=v.size(); i<size; ++i) {
         cout << "Final count is: " << v[i] << endl;
    }

    return 0;
}

