#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <cassert>

using boost::asio::ip::tcp;

void test_server() {
    try {
        // Connect to the server
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345));

        // Read response
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket, buffer, "\n");

        std::istream is(&buffer);
        std::string response;
        std::getline(is, response);

        // Check response
        assert(response == "Hello from the server!");
        std::cout << "Test passed: Received correct response from the server!" << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        assert(false);
    }
}

int main() {
    std::cout << "Starting server test..." << std::endl;

    // Run the server in a separate thread
    std::thread server_thread([] {
        std::system("./rtype_server &"); // Assuming the server binary is named `rtype_server`
    });

    // Give the server some time to start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Run the test
    test_server();

    // Clean up
    server_thread.detach(); // In production, you'd want a cleaner shutdown mechanism
    return 0;
}
