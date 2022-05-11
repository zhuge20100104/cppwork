#include "web_socket/broadcast_server.h"

#include <gtest/gtest.h>

GTEST_TEST(BroadCastServerTests, ServerStart) {
    try {
        broadcast_server server_instance;

        // Start a thread to run the processing loop
        thread t(bind(&broadcast_server::process_messages, &server_instance));

        // Run the asio loop with the main thread
        server_instance.run(9002);

        t.join();

    } catch (websocketpp::exception const& e) {
        std::cout << e.what() << std::endl;
    }
}