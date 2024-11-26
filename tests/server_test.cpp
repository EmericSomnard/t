#include <iostream>
#include <boost/asio.hpp>
#include <cassert>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

void test_server() {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);

        bool connected = false;
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
            return;
        }

        std::cout << "Connexion établie avec succès au serveur." << std::endl;

        socket.close();
        std::cout << "Connexion fermée immédiatement après la connexion." << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Test échoué: " << e.what() << std::endl;
        assert(false);
    }
}

int main() {
    std::cout << "Démarrage du test du serveur..." << std::endl;

    std::thread server_thread([] {
        std::system("./server_test");
    });

    test_server();

    server_thread.join();

    return 0;
}
