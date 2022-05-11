#include <iostream>
using std::cout;
using std::endl;

#include <boost/asio.hpp>
#include <thread>

#include <boost/date_time/posix_time/posix_time.hpp>

using std::thread;
using namespace boost::asio;


class Printer {
    public:
        Printer(io_service& io): strand_(io),  timer1_(io, boost::posix_time::seconds(1)),
                            timer2_(io, boost::posix_time::seconds(1)), count_(0) {
                                timer1_.async_wait(strand_.wrap([this](const auto& ec){this->print1(); } ));
                                timer2_.async_wait(strand_.wrap([this](const auto& ec){this->print2(); }));
                            }
    
        ~Printer() {
            cout << "Final count is: " << count_ << endl;
        }

        void print1() {
        
            if(count_ < 10) {
                cout << "Timer1: " << count_ << endl;
                ++count_;
                timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
                timer1_.async_wait(strand_.wrap([this](const auto& ec){ this->print1(); }  ));
            }
        }

        void print2() {
            if(count_ < 10) {
                cout << "Timer2: " << count_ << endl;
                ++count_;
                timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
                timer2_.async_wait(strand_.wrap([this](const auto& ec) { this->print2(); }));
            }
        }

        
    
    private:
        io_service::strand strand_;
        deadline_timer timer1_;
        deadline_timer timer2_;
        int count_;
};


int main() {
    io_service io;
    Printer p(io);
    
    thread t(
                [&io](){
                    cout << "second thread start" << endl;;
                    io.run();
                    cout << "second thread end" << endl;
                }
            );

    io.run();
    // 等待子线程完成
    t.join();

    return 0;
}
