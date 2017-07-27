#include "ConnectionManager.h"

ConnectionManager& ConnectionManager::get()
{
	static ConnectionManager connectionManager;
	return connectionManager;
}

void ConnectionManager::sendMessageToServer(unsigned short port, std::string ip, std::string message)
{
	
	// Ask for the server address
	sf::IpAddress server(ip);

	// Send a message to the server
	//const char out[] = "Hi, I'm a client";

	// message.length() + 1 for null terminated string
	if (socket.send(message.c_str(), message.length() + 1, server, port) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the server: \"" << message << "\"" << std::endl;
}

ConnectionManager::ConnectionManager()
{
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
	// Receive an answer from anyone (but most likely from the server)
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;
}
