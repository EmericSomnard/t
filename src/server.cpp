#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void start_server() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 58920));
        std::cout << "Server is running on port 57920..." << std::endl;

        tcp::socket socket(io_context);
        acceptor.accept(socket);
        std::cout << "Client connected!" << std::endl;

        std::string message = "Hello from the server!\n";
        boost::asio::write(socket, boost::asio::buffer(message));
        std::cout << "Message sent to the client: " << message << std::endl;

        socket.close();
        std::cout << "Connection closed with client." << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Starting server..." << std::endl;
    start_server();
    return 0;
}
