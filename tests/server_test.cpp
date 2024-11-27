#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <csignal>

using boost::asio::ip::tcp;

// Fonction pour démarrer le serveur dans un thread séparé
void run_server() {
    std::system("../build/rtype_server");  // Chemin vers l'exécutable du serveur
}

void test_server() {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);

        // Essayer de se connecter au serveur pendant un court délai
        for (int i = 0; i < 5; ++i) {
            try {
                socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 53920));
                std::cout << "Connexion réussie avant l'arrêt." << std::endl;
                break;
            } catch (const boost::system::system_error& e) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "Tentative de connexion échouée, réessaye..." << std::endl;
            }
        }

        // Envoyer un signal pour arrêter le serveur
        std::raise(SIGINT);  // Simuler l'arrêt du serveur

        // Après l'arrêt, vérifier si la connexion échoue
        try {
            socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 53920));
            std::cout << "Erreur: La connexion devrait avoir échoué après l'arrêt du serveur." << std::endl;
        } catch (const boost::system::system_error& e) {
            std::cout << "Test réussi: Le serveur est bien arrêté, connexion échouée." << std::endl;
        }

    } catch (std::exception &e) {
        std::cerr << "Test échoué: " << e.what() << std::endl;
        assert(false);
    }
}

int main() {
    std::cout << "Démarrage du test du serveur..." << std::endl;

    std::thread server_thread(run_server);  // Démarre le serveur dans un thread

    std::this_thread::sleep_for(std::chrono::seconds(1));  // Attends que le serveur soit prêt

    test_server();  // Exécute le test de connexion

    std::cout << "Envoi du signal pour arrêter le serveur..." << std::endl;
    std::raise(SIGINT);  // Envoi du signal pour arrêter le serveur

    server_thread.join();  // Attends que le serveur termine

    std::cout << "Test terminé, serveur arrêté." << std::endl;

    return 0;
}
