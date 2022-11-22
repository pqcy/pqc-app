#include "tcpserver.h"

#include <mutex>

bool TcpServer::start(int port) {
	// TO DO

	acceptThread_ = new std::thread(&TcpServer::acceptRun, this);
	return true;
}

bool TcpServer::stop() {
	// TO DO
	if (acceptThread_ != nullptr) {
		delete acceptThread_;
		acceptThread_ = nullptr;
	}
	return true;
}

void TcpServer::acceptRun() {
	while (true) {
		// TO DO
		// int newsock = accept(...);
		int newsock = 1;
		new std::thread(&TcpServer::_run, newsock);
	}
}

void TcpServer::_run(int newsock) {
	{
		std::lock_guard<std::mutex> lock(m_);
		sessions_.push_back(session);

		threads_.push_back(runThread);
	}

}
