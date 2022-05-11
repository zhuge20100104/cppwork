#include <iostream>

using std::cout;
using std::endl;

#include <memory>
using std::shared_ptr;

#include <boost/asio.hpp>

#include <vector>
using std::vector;

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;

class Printer {
    public:
        Printer(io_service& io):timer_(io, boost::posix_time::seconds(1)), count_(0) {
            timer_.async_wait([this](const auto& ec){

                        if(ec == boost::asio::error::operation_aborted) {
                            cout << "cancel now" << endl; 
                        } else 
                            this->print();
                    });
        }

        ~Printer() {
            cout << "Final count is count: " << count_ << endl;
        }

        void print() {
            if(count_ < 5) {
            
                cout << count_ << endl;
                ++count_;
                timer_.expires_at(timer_.expires_at()+boost::posix_time::seconds(1));
                timer_.async_wait([this](const auto& ec){
                        if(ec == boost::asio::error::operation_aborted) {
                            cout << "cancel now" << endl;
                        } else 
                            this->print();
                    });
            }
        }

    private:
        deadline_timer timer_;
        int count_;
};

int main() {
    io_service io;

    {
        Printer p(io);
    }
    io.run();

    return 0;
}

