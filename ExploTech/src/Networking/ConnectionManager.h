#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>
#include "../World/Chunk/WorldManager.h"
#include "../World/Block/BlockChange.h"

class ConnectionManager
{
	public:
		static ConnectionManager& get();

		void sendMessageToServer(unsigned short port, std::string ip, BlockChange blockChange);

	private:
		ConnectionManager();
		~ConnectionManager();

		void receiveData();

		bool m_isRunning = true;
		std::vector<std::thread> m_threads;

		// Create a socket for communicating with the server
		sf::UdpSocket socket;
};