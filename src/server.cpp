#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void start_server() {
    try {
        boost::asio::io_context io_context;

        // Create an endpoint listening on port 12345
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 123456));
        std::cout << "Server is running on port 12345..." << std::endl;

        while (true) {
            // Accept a connection
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::cout << "Client connected!" << std::endl;

            // Send a welcome message
            std::string message = "Hello from the server!\n";
            boost::asio::write(socket, boost::asio::buffer(message));
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Starting server..." << std::endl;
    start_server();
    return 0;
}
