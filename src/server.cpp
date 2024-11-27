#include <csignal>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

volatile bool stop_server = false;

void handle_signal(int signal) {
    if (signal == SIGINT) {
        stop_server = true;
    }
}

void start_server() {
    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 58920));
        std::cout << "Server is running on port 58920..." << std::endl;

        while (!stop_server) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "Client connected!" << std::endl;
            std::string message = "Hello from the server!\n";
            boost::asio::write(socket, boost::asio::buffer(message));
            socket.close();
            std::cout << "Connection closed with client." << std::endl;
        }

        std::cout << "Server shutting down..." << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::signal(SIGINT, handle_signal);

    std::cout << "Starting server..." << std::endl;
    start_server();

    return 0;
}
