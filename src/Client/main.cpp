#include <SFML/Network.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    sf::TcpSocket socket;
    if (socket.connect(sf::IpAddress::LocalHost, 12456) != sf::Socket::Done) {
        std::cerr << "unable to connect to 127.0.0.1:12456" << std::endl;
        return 1;
    }

    sf::Packet packet;
    if (socket.receive(packet) != sf::Socket::Done) {
        std::cerr << "unable to receive data" << std::endl;
        socket.disconnect();
        return 1;
    }

    std::string msg;
    packet >> msg;

    std::cout << "received " << msg << std::endl;

    socket.disconnect();

    return 0;
}
