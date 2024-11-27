#include <iostream>
#include <boost/asio.hpp>
#include <cassert>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

// Fonction pour démarrer le serveur dans un thread séparé
void run_server() {
    std::system("../src/server"); // Assurez-vous que le serveur est dans le PATH ou donnez un chemin absolu
}

void test_server() {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);

        bool connected = false;

        // Essayer de se connecter au serveur (5 tentatives)
        for (int i = 0; i < 5; ++i) {
            try {
                socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 58920));
                connected = true;
                break;
            } catch (const boost::system::system_error& e) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "Tentative de connexion échouée, réessaye..." << std::endl;
            }
        }

        if (!connected) {
            std::cerr << "Erreur: Impossible de se connecter au serveur." << std::endl;
            assert(false);
            return;
        }

        std::cout << "Connexion établie avec succès au serveur." << std::endl;

        // Lire les données envoyées par le serveur
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket, buffer, "\n");

        // Convertir les données reçues en chaîne
        std::istream input(&buffer);
        std::string message;
        std::getline(input, message);

        // Valider le message reçu
        std::cout << "Message reçu du serveur: " << message << std::endl;
        assert(message == "Hello from the server!");

        std::cout << "Test réussi : Le message correspond aux attentes." << std::endl;

        // Fermer la connexion
        socket.close();
        std::cout << "Connexion fermée." << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Test échoué: " << e.what() << std::endl;
        assert(false);
    }
}

int main() {
    std::cout << "Démarrage du test du serveur..." << std::endl;

    // Lancer le serveur dans un thread séparé
    std::thread server_thread(run_server);

    // Donner au serveur le temps de démarrer
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Lancer les tests
    test_server();

    // Terminer le thread du serveur proprement
    server_thread.detach(); // Vous pouvez aussi implémenter un signal pour arrêter le serveur

    return 0;
}
