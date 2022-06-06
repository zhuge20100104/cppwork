#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>

#include <chrono>
#include <iostream>
using std::cout;
using std::endl;

using namespace boost::asio;

int main(void) {
    
    io_service io;
    steady_timer st(io);
    st.expires_from_now(std::chrono::seconds(5));
    
    st.wait();
    
    cout << "Hello world" << endl;

    return 0;
}

