#include <SFML/Network.hpp>
#include <iostream>

#include "../TileMap/TileMap.h"

int main(int argc, char *argv[])
{
    sf::TcpListener listener;
    if (listener.listen(12456)) {
        std::cerr << "unable to listen to ::12456" << std::endl;
        return 1;
    }
    std::cout << "waiting for clients" << std::endl;

    sf::TcpSocket client;
    if (listener.accept(client) != sf::TcpSocket::Done) {
        std::cerr << "unable to accept incoming client" << std::endl;
        listener.close();
        return 1;
    }
    std::cout << "new client connected" << std::endl;

    TileMap tileMap();

    sf::Packet packet;
    packet << msg;

    if (client.send(packet) != sf::Socket::Done) {
        std::cerr << "unable to send message to client" << std::endl;
        client.disconnect();
        listener.close();
        return 1;
    }

    client.disconnect();
    listener.close();

    return 0;
}
