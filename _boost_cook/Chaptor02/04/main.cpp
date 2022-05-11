#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/thread.hpp>
#include <boost/shared_array.hpp>

#include <cstring>

void do_process(const char* data, std::size_t size);

void do_process_in_background(const char* data, std::size_t size) {
    char* data_cpy = new char[size];
    std::memcpy(data_cpy, data, size);
    boost::thread([data_cpy, size](){
        do_process(data_cpy, size);
    });
}

void do_process_shared_array(const boost::shared_array<char>& data, std::size_t size) {
    do_process(data.get(), size);
}

void do_process_in_background_v1(const char* data, std::size_t size) {
    boost::shared_array<char> data_cpy(new char[size]);
    std::memcpy(data_cpy.get(), data, size);
    auto self(data_cpy);
    boost::thread([self, size](){
        do_process_shared_array(self, size);
    }).detach();
}


void do_process_shared_ptr(const boost::shared_ptr<char[]>& data, std::size_t size) {
    do_process(data.get(), size);
}

void do_process_in_background_v2(const char* data, std::size_t size) {
    boost::shared_ptr<char[]> data_cpy = boost::make_shared<char[]>(size);
    std::memcpy(data_cpy.get(), data, size);
    auto self(data_cpy);

    boost::thread([self, size]() {
        do_process_shared_ptr(self, size);
    }).detach();
}

void do_process_shared_ptr2(const boost::shared_ptr<char>& data, std::size_t size) {
    do_process(data.get(), size);
}

void do_process_in_background_v3(const char* data, std::size_t size) {
    boost::shared_ptr<char> data_cpy(
        new char[size],
        boost::checked_array_deleter<char>()
    );

    std::memcpy(data_cpy.get(), data, size);
    auto self(data_cpy);
    boost::thread([self, size]() {
        do_process_shared_ptr2(self, size);
    }).detach();
}

void do_process(const char* data, std::size_t size) {
    assert(size);
    assert(data);
}

int main(int argc, char* argv[]) {
    char ch[] = "Hello, dear reader";
    do_process_in_background_v1(ch, sizeof(ch));
    do_process_in_background_v2(ch, sizeof(ch));
    do_process_in_background_v3(ch, sizeof(ch));

    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    return 0;
}

