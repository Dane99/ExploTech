#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>

class ConnectionManager
{
	public:
		static ConnectionManager& get();

		void startClient(unsigned short port, std::string ip, std::string message);

	private:
		ConnectionManager();
		~ConnectionManager();

		void maintainConnection();

		bool m_isRunning = true;
		std::vector<std::thread> m_threads;

		// Create a socket for communicating with the server
		sf::UdpSocket socket;
};