#include <csignal>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

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
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 53920));
        std::cout << "Server is running on port 53920..." << std::endl;

        tcp::socket socket(io_context);
        acceptor.accept(socket);
        std::cout << "Client connected!" << std::endl;

        while (!stop_server) {
            boost::system::error_code ec;
            char data[1];
            size_t length = socket.read_some(boost::asio::buffer(data), ec);

            if (ec == boost::asio::error::eof) {
                std::cout << "Client disconnected. Stopping server." << std::endl;
                stop_server = true;
                break;
            } else if (ec) {
                throw boost::system::system_error(ec);
            }

            // Traiter les données reçues si nécessaire
        }

        std::cout << "Server shutting down..." << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::signal(SIGINT, handle_signal);

    std::cout << "Starting server..." << std::endl;
    std::thread server_thread(start_server);

    server_thread.join();

    std::cout << "Server has stopped." << std::endl;

    return 0;
}
