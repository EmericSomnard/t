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
                socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 47920));
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

        boost::asio::streambuf buffer;
        boost::asio::read_until(socket, buffer, "\n");

        std::istream is(&buffer);
        std::string response;
        std::getline(is, response);

        assert(response == "Hello from the server!");
        std::cout << "Test passed: Received correct response from the server!" << std::endl;

        socket.close();
        std::cout << "Connexion fermée proprement." << std::endl;

    } catch (std::exception &e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        assert(false);
    }
}

int main() {
    std::cout << "Starting server test..." << std::endl;

    std::thread server_thread([] {
        std::system("./server_test");
    });

    test_server();

    server_thread.join();

    return 0;
}
