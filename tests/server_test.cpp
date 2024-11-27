#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <csignal> // Pour gérer les signaux

using boost::asio::ip::tcp;

// Fonction pour démarrer le serveur dans un thread séparé
void run_server() {
    std::system("../build/rtype_server"); // Chemin vers l'exécutable du serveur
}

void test_server() {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);

        bool connected = false;

        for (int i = 0; i < 5; ++i) {
            try {
                socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 38920));
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

        boost::asio::streambuf buffer;
        boost::asio::read_until(socket, buffer, "\n");

        std::istream input(&buffer);
        std::string message;
        std::getline(input, message);

        std::cout << "Message reçu du serveur: " << message << std::endl;
        assert(message == "Hello from the server!");

        std::cout << "Test réussi : Le message correspond aux attentes." << std::endl;

        socket.close();
        std::cout << "Connexion fermée." << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Test échoué: " << e.what() << std::endl;
        assert(false);
    }
}

int main() {
    std::cout << "Démarrage du test du serveur..." << std::endl;

    std::thread server_thread(run_server);

    std::this_thread::sleep_for(std::chrono::seconds(1));


    test_server();

    std::cout << "Envoi du signal pour arrêter le serveur..." << std::endl;
    std::raise(SIGINT);

    server_thread.join();

    std::cout << "Test terminé, serveur arrêté." << std::endl;

    return 0;
}
