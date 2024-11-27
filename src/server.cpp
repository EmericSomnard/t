#include <csignal>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <atomic>

using boost::asio::ip::tcp;

// Variable atomique pour arrêter le serveur
std::atomic<bool> stop_server(false);

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
            socket.close();  // Fermeture de la connexion avec le client

            std::cout << "Connection closed with client." << std::endl;

            // Si on doit arrêter le serveur, on sort de la boucle
            if (stop_server) {
                std::cout << "Server is shutting down gracefully..." << std::endl;
                break;
            }
        }

        std::cout << "Server shutting down..." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    // Gérer le signal SIGINT pour arrêter le serveur proprement
    std::signal(SIGINT, handle_signal);

    std::cout << "Starting server..." << std::endl;

    // Lancer le serveur dans un thread séparé
    std::thread server_thread(start_server);

    // Simuler un délai (peut être ajusté selon le besoin)
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Envoi du signal pour arrêter le serveur
    std::cout << "Sending stop signal to server..." << std::endl;
    stop_server = true;  // Le serveur va sortir de la boucle d'acceptation

    // Attendre que le thread du serveur se termine
    server_thread.join();

    std::cout << "Server stopped." << std::endl;

    return 0;
}
