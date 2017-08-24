#include "ConnectionManager.h"

ConnectionManager& ConnectionManager::get()
{
	static ConnectionManager connectionManager;
	return connectionManager;
}

void ConnectionManager::sendMessageToServer(unsigned short port, std::string ip, BlockChange blockChange)
{
	// Socket will pick a unused port automagically.
	//socket.bind(1121);

	// Ask for the server address
	sf::IpAddress server(ip);

	sf::Packet packet;
	packet << blockChange.worldPosition.x << blockChange.worldPosition.y << blockChange.worldPosition.z << blockChange.type;

	if (socket.send(packet, server, port) != sf::Socket::Done)
	{
		return;
	}

	std::cout << "Message sent to the server." << std::endl;
}

ConnectionManager::ConnectionManager()
{
	socket.setBlocking(false);

	m_threads.emplace_back([&]()
	{
		while (m_isRunning)
		{
			receiveData();
			std::this_thread::sleep_for(std::chrono::microseconds(100));
		}
	});

}


ConnectionManager::~ConnectionManager()
{
	m_isRunning = false;
	for (auto& thread : m_threads)
	{
		thread.join();
	}
}

void ConnectionManager::receiveData()
{
	// Receive an answer from anyone (but most likely from the server).
	sf::IpAddress sender;
	unsigned short senderPort;
	sf::Packet packet;

	if (socket.receive(packet, sender, senderPort) != sf::Socket::Done)
		return;

	BlockChange blockChange;
	if (packet >> blockChange.worldPosition.x >> blockChange.worldPosition.y >> blockChange.worldPosition.z >> blockChange.type) {
		std::cout << "X: " << blockChange.worldPosition.x << " Y: " << blockChange.worldPosition.y << " Z: " << blockChange.worldPosition.z << " Type: " << blockChange.type << std::endl;
		//World_Manager::get().addThreadSafeServerBlockChangesToTheList(blockChange.worldPosition, static_cast<Block::ID>(blockChange.type), true);
	}

	std::cout << "Message received from " << sender << std::endl;
}
