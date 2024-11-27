#include <csignal>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

using boost::asio::ip::tcp;

volatile bool stop_server = false;  // Variable globale pour indiquer si le serveur doit s'arrêter

// Fonction pour gérer le signal SIGINT
void handle_signal(int signal) {
    if (signal == SIGINT) {
        stop_server = true;
    }
}

void start_server() {
    try {
        boost::asio::io_context io_context;  // Créer le contexte d'IO pour gérer les connexions réseau
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 18720));  // Écouter sur le port 58920

        std::cout << "Server is running on port 58920..." << std::endl;

        // Exécuter le serveur tant que le signal d'arrêt n'est pas reçu
        while (!stop_server) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);  // Accepter une nouvelle connexion

            std::cout << "Client connected!" << std::endl;
            std::string message = "Hello from the server!\n";
            boost::asio::write(socket, boost::asio::buffer(message));  // Envoyer un message au client
            socket.close();  // Fermer la connexion avec le client
            std::cout << "Connection closed with client." << std::endl;
        }

        std::cout << "Server shutting down..." << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    // Capturer le signal SIGINT pour permettre d'arrêter le serveur
    std::signal(SIGINT, handle_signal);

    std::cout << "Starting server..." << std::endl;
    
    std::thread server_thread(start_server);  // Lancer le serveur dans un thread séparé

    // Exécuter le contexte d'IO dans un thread principal
    std::this_thread::sleep_for(std::chrono::seconds(10));  // Attendre un peu avant de tenter d'arrêter le serveur

    std::cout << "Sending stop signal to server..." << std::endl;
    std::raise(SIGINT);  // Envoyer un signal SIGINT pour arrêter le serveur


    return 0;
}
