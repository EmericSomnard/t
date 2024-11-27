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
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 58920));

        std::cout << "Server is running on port 58920..." << std::endl;

        // Boucle principale d'écoute
        while (!stop_server) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "Client connected!" << std::endl;
            std::string message = "Hello from the server!\n";
            boost::asio::write(socket, boost::asio::buffer(message));
            socket.close();  // Fermer la connexion avec le client

            std::cout << "Connection closed with client." << std::endl;
        }

        std::cout << "Server shutting down..." << std::endl;
        // Libération des ressources (fermeture propre)
        io_context.stop();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::signal(SIGINT, handle_signal);  // Enregistrer le gestionnaire de signal

    std::cout << "Starting server..." << std::endl;

    std::thread server_thread(start_server);  // Lancer le serveur dans un thread séparé

    std::this_thread::sleep_for(std::chrono::seconds(10));  // Attendre un peu pour laisser le serveur démarrer

    std::cout << "Sending stop signal to server..." << std::endl;
    std::raise(SIGINT);  // Envoyer le signal d'arrêt (SIGINT)

    server_thread.join();  // Attendre que le serveur se ferme correctement

    std::cout << "Server has stopped." << std::endl;

    return 0;
}
