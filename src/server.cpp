#include <iostream>
#include <boost/asio.hpp>
#include <csignal>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

bool running = true;

void signal_handler(int signal) {
    if (signal == SIGINT) {
        std::cout << "Stopping server..." << std::endl;
        running = false;
    }
}

void start_server() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 58920));
        std::cout << "Server is running on port 58920..." << std::endl;

        while (running) { // Boucle pour accepter plusieurs connexions
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "Client connected from: " 
                      << socket.remote_endpoint().address().to_string() 
                      << ":" << socket.remote_endpoint().port() << std::endl;

            std::string message = "Hello from the server!\n";
            boost::asio::write(socket, boost::asio::buffer(message));
            std::cout << "Message sent to the client: " << message << std::endl;

            socket.close();
            std::cout << "Connection closed with client." << std::endl;

            // Petit délai pour éviter une boucle trop rapide
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::signal(SIGINT, signal_handler);

    std::cout << "Starting server..." << std::endl;
    start_server();
    return 0;
}
